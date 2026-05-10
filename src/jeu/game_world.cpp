#include "game_world.hpp"

#include "game_config.hpp"
#include "../tours/tour_factory.hpp"

#include <algorithm>
#include <iostream>

GameWorld::GameWorld(
    const std::string& cheminCarte,
    int argentInitial,
    int viesInitiales,
    int premiereVague
)
    : carte_(cheminCarte),
      joueur_(argentInitial, viesInitiales),
      numeroVague_(premiereVague)
{
}

void GameWorld::update(float dt, TextureManager& textureManager)
{
    waveManager_.update(dt, ennemis_, carte_.getChemin());

    for (auto& ennemi : ennemis_)
    {
        if (ennemi->getType() == TypeEnnemi::Regular)
        {
            ennemi->setTexture(textureManager.get("ennemi_regular"));
        }

        if (ennemi->getType() == TypeEnnemi::Fast)
        {
            ennemi->setTexture(textureManager.get("ennemi_fast"));
        }

        if (ennemi->getType() == TypeEnnemi::Strong)
        {
            ennemi->setTexture(textureManager.get("ennemi_strong"));
        }

        if (ennemi->getType() == TypeEnnemi::Armored)
        {
            ennemi->setTexture(textureManager.get("ennemi_armored"));
        }

        if (ennemi->getType() == TypeEnnemi::Heli)
        {
            ennemi->setTexture(textureManager.get("ennemi_heli"));
        }

        if (ennemi->getType() == TypeEnnemi::Jet)
        {
            ennemi->setTexture(textureManager.get("ennemi_jet"));
        }
    }

    mettreAJourEnnemis(dt);
    mettreAJourTours(dt);
    mettreAJourProjectiles(dt);
    gererEnnemisMortsEtArrives(GameConfig::ARGENT_PAR_ENNEMI_TUE);
}

std::optional<int> GameWorld::preparerAchatTour(
    TypeTour typeTour,
    TextureManager& textureManager
)
{
    std::unique_ptr<Tour> preview =
        TourFactory::creerTour(typeTour, 0, 0, textureManager);

    if (!preview)
    {
        return std::nullopt;
    }

    int cout = preview->getCout();
    if (!joueur_.payer(cout))
    {
        std::cout << "Pas assez d'argent. Cout = "
                  << cout
                  << ", argent = "
                  << joueur_.getArgent()
                  << std::endl;
        return std::nullopt;
    }

    return cout;
}

bool GameWorld::placerTour(
    TypeTour typeTour,
    int gridX,
    int gridY,
    TextureManager& textureManager
)
{
    if (!carte_.estConstructible(gridX, gridY))
    {
        std::cout << "Impossible : construction seulement sur les cases @"
                  << std::endl;
        return false;
    }

    if (tourExisteDeja(gridX, gridY))
    {
        std::cout << "Impossible : une tour existe deja ici"
                  << std::endl;
        return false;
    }

    std::unique_ptr<Tour> nouvelleTour =
        TourFactory::creerTour(typeTour, gridX, gridY, textureManager);

    if (!nouvelleTour)
    {
        return false;
    }

    int cout = nouvelleTour->getCout();

    if (!joueur_.payer(cout))
    {
        std::cout << "Pas assez d'argent. Cout = "
                  << cout
                  << ", argent = "
                  << joueur_.getArgent()
                  << std::endl;
        return false;
    }

    tours_.push_back(std::move(nouvelleTour));

    std::cout << "Tour ajoutee en "
              << gridX
              << ", "
              << gridY
              << " | Cout : "
              << cout
              << " | Argent restant : "
              << joueur_.getArgent()
              << std::endl;

    return true;
}

bool GameWorld::placerTourDejaPayee(
    TypeTour typeTour,
    int gridX,
    int gridY,
    TextureManager& textureManager
)
{
    if (!carte_.estConstructible(gridX, gridY))
    {
        return false;
    }

    if (tourExisteDeja(gridX, gridY))
    {
        return false;
    }

    std::unique_ptr<Tour> nouvelleTour =
        TourFactory::creerTour(typeTour, gridX, gridY, textureManager);

    if (!nouvelleTour)
    {
        return false;
    }

    tours_.push_back(std::move(nouvelleTour));

    std::cout << "Tour ajoutee en "
              << gridX
              << ", "
              << gridY
              << " | Argent restant : "
              << joueur_.getArgent()
              << std::endl;

    return true;
}

bool GameWorld::ameliorerTour(int gridX, int gridY)
{
    int indexTour = trouverIndexTour(gridX, gridY);
    if (indexTour == -1)
    {
        std::cout << "Aucune tour sous le curseur." << std::endl;
        return false;
    }

    Tour& tour = *tours_[indexTour];
    if (!tour.peutAmeliorer())
    {
        std::cout << "Cette tour est deja niveau max" << std::endl;
        return false;
    }

    int coutAmelioration = tour.getCoutAmelioration();

    if (!joueur_.payer(coutAmelioration))
    {
        std::cout << "Pas assez d'argent pour ameliorer. Cout = "
                  << coutAmelioration
                  << ", argent = "
                  << joueur_.getArgent()
                  << std::endl;
        return false;
    }

    if (!tour.ameliorer())
    {
        std::cout << "Amelioration impossible." << std::endl;
        return false;
    }

    std::cout << "Tour amelioree. Niveau : "
              << tour.getNiveau()
              << " | Argent restant : "
              << joueur_.getArgent()
              << std::endl;

    return true;
}

bool GameWorld::vendreTour(int gridX, int gridY)
{
    int indexTour = trouverIndexTour(gridX, gridY);
    if (indexTour == -1)
    {
        std::cout << "Aucune tour sous le curseur." << std::endl;
        return false;
    }

    int prixVente = tours_[indexTour]->getPrixVente();
    joueur_.ajouterArgent(prixVente);
    tours_.erase(tours_.begin() + indexTour);

    std::cout << "Tour vendue pour "
              << prixVente
              << " | Argent actuel : "
              << joueur_.getArgent()
              << std::endl;

    return true;
}

void GameWorld::lancerVague()
{
    if (!ennemis_.empty())
    {
        std::cout << "Vague pas finis" << std::endl;
        return;
    }

    waveManager_.lancerVague(numeroVague_);

    std::cout << "Vague "
              << numeroVague_
              << " lancee"
              << std::endl;

    numeroVague_++;
}

int GameWorld::trouverIndexTour(int gridX, int gridY) const
{
    for (int i = 0; i < static_cast<int>(tours_.size()); i++)
    {
        if (tours_[i]->getGridX() == gridX &&
            tours_[i]->getGridY() == gridY)
        {
            return i;
        }
    }

    return -1;
}

bool GameWorld::tourExisteDeja(int gridX, int gridY) const
{
    return std::any_of(
        tours_.begin(),
        tours_.end(),
        [gridX, gridY](const std::unique_ptr<Tour>& tour)
        {
            return tour->getGridX() == gridX && tour->getGridY() == gridY;
        }
    );
}

void GameWorld::mettreAJourEnnemis(float dt)
{
    for (auto& ennemi : ennemis_)
    {
        ennemi->update(dt, carte_.getChemin());
    }
}

void GameWorld::mettreAJourTours(float dt)
{
    for (auto& tour : tours_)
    {
        tour->update(
            dt,
            ennemis_,
            projectiles_,
            carte_.getTailleCase()
        );
    }
}

void GameWorld::mettreAJourProjectiles(float dt)
{
    for (auto& projectile : projectiles_)
    {
        projectile.update(dt, ennemis_);
    }

    projectiles_.erase(
        std::remove_if(
            projectiles_.begin(),
            projectiles_.end(),
            [](const Projectile& projectile)
            {
                return projectile.estTermine();
            }
        ),
        projectiles_.end()
    );
}

void GameWorld::gererEnnemisMortsEtArrives(int argentParEnnemi)
{
    int ennemisArrives = 0;
    int argentGagne = 0;

    for (const auto& ennemi : ennemis_)
    {
        if (ennemi->estArrive())
        {
            ennemisArrives++;
        }

        if (ennemi->estMort())
        {
            argentGagne += argentParEnnemi;
        }
    }

    if (argentGagne > 0)
    {
        joueur_.ajouterArgent(argentGagne);

        std::cout << "Argent gagne : +"
                  << argentGagne
                  << " | Argent total : "
                  << joueur_.getArgent()
                  << std::endl;
    }

    if (ennemisArrives > 0)
    {
        joueur_.perdreVie(ennemisArrives);

        std::cout << ennemisArrives
                  << " ennemi(s) arrive(s). Vies restantes : "
                  << joueur_.getVies()
                  << std::endl;
    }

    ennemis_.erase(
        std::remove_if(
            ennemis_.begin(),
            ennemis_.end(),
            [](const std::unique_ptr<Ennemi>& ennemi)
            {
                return ennemi->estMort() || ennemi->estArrive();
            }
        ),
        ennemis_.end()
    );
}
