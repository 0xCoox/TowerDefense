#include "jeu.hpp"

#include "../tours/tour_factory.hpp"

#include <SDL2/SDL.h>

#include <algorithm>
#include <iostream>
#include <string>

namespace
{
    constexpr int LARGEUR_FENETRE = 720;
    constexpr int HAUTEUR_FENETRE = 720;

    constexpr int ARGENT_INITIAL = 250;
    constexpr int VIES_INITIALES = 20;

    constexpr int PREMIERE_VAGUE = 1;
    constexpr int TYPE_TOUR_PAR_DEFAUT = 1;

    constexpr int CURSEUR_X_INITIAL = 0;
    constexpr int CURSEUR_Y_INITIAL = 0;

    constexpr int ARGENT_PAR_ENNEMI_TUE = 5;

    constexpr int COULEUR_FOND_R = 0;
    constexpr int COULEUR_FOND_G = 0;
    constexpr int COULEUR_FOND_B = 0;
    constexpr int COULEUR_FOND_A = 255;

    constexpr int COULEUR_CURSEUR_R = 255;
    constexpr int COULEUR_CURSEUR_G = 255;
    constexpr int COULEUR_CURSEUR_B = 255;
    constexpr int COULEUR_CURSEUR_A = 255;

    constexpr int TAILLE_POLICE_HUD = 24;

    const std::string CHEMIN_POLICE_HUD =
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
}

Jeu::Jeu()
    : window_("Tower Defense", LARGEUR_FENETRE, HAUTEUR_FENETRE),
      rendu_(window_.getNativeWindow()),
      carte_("assets/map.txt"),
      input_(),
      hud_(CHEMIN_POLICE_HUD, TAILLE_POLICE_HUD),
      estLance_(true),
      estPause_(false),
      joueur_(ARGENT_INITIAL, VIES_INITIALES),
      numeroVague_(PREMIERE_VAGUE),
      curseurX_(CURSEUR_X_INITIAL),
      curseurY_(CURSEUR_Y_INITIAL),
      typeTourSelectionne_(TYPE_TOUR_PAR_DEFAUT),
      dernierTemps_(std::chrono::steady_clock::now())
{
    afficherCommandes();
}

void Jeu::lancer()
{
    while (estLance_)
    {
        auto tempsActuel = std::chrono::steady_clock::now();
        std::chrono::duration<float> tempsEcoule = tempsActuel - dernierTemps_;

        float dt = tempsEcoule.count();
        dernierTemps_ = tempsActuel;

        traiterEntrees();

        if (!estPause_)
        {
            mettreAJour(dt);
        }

        dessiner();
    }
}

void Jeu::traiterEntrees()
{
    input_.update();

    if (input_.shouldQuit() || input_.isKeyPressed(SDLK_ESCAPE))
    {
        estLance_ = false;
    }

    if (input_.isKeyPressed(SDLK_SPACE))
    {
        estPause_ = !estPause_;

        if (estPause_)
        {
            std::cout << "Pause" << std::endl;
        }
        else
        {
            std::cout << "Reprise" << std::endl;
        }
    }

    if (input_.isKeyPressed(SDLK_RETURN))
    {
        waveManager_.lancerVague(numeroVague_);

        std::cout << "Vague " << numeroVague_ << " lancee" << std::endl;

        numeroVague_++;
    }

    if (input_.isKeyPressed(SDLK_UP))
    {
        curseurY_--;
    }

    if (input_.isKeyPressed(SDLK_DOWN))
    {
        curseurY_++;
    }

    if (input_.isKeyPressed(SDLK_LEFT))
    {
        curseurX_--;
    }

    if (input_.isKeyPressed(SDLK_RIGHT))
    {
        curseurX_++;
    }

    if (input_.isKeyPressed(SDLK_1))
    {
        selectionnerTour(1);
    }

    if (input_.isKeyPressed(SDLK_2))
    {
        selectionnerTour(2);
    }

    if (input_.isKeyPressed(SDLK_3))
    {
        selectionnerTour(3);
    }

    if (input_.isKeyPressed(SDLK_4))
    {
        selectionnerTour(4);
    }

    if (input_.isKeyPressed(SDLK_5))
    {
        selectionnerTour(5);
    }

    if (input_.isKeyPressed(SDLK_a))
    {
        essayerAjouterTour();
    }
}

void Jeu::mettreAJour(float dt)
{
    waveManager_.update(dt, ennemis_, carte_.getChemin());

    mettreAJourEnnemis(dt);
    mettreAJourTours(dt);
    mettreAJourProjectiles(dt);

    gererEnnemisMortsEtArrives();

    if (joueur_.estMort())
    {
        std::cout << "Game Over !" << std::endl;
        estLance_ = false;
    }
}

void Jeu::mettreAJourEnnemis(float dt)
{
    for (auto& ennemi : ennemis_)
    {
        ennemi->update(dt, carte_.getChemin());
    }
}

void Jeu::mettreAJourTours(float dt)
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

void Jeu::mettreAJourProjectiles(float dt)
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

void Jeu::gererEnnemisMortsEtArrives()
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
            argentGagne += ARGENT_PAR_ENNEMI_TUE;
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

void Jeu::dessiner()
{
    rendu_.setColor(
        COULEUR_FOND_R,
        COULEUR_FOND_G,
        COULEUR_FOND_B,
        COULEUR_FOND_A
    );

    rendu_.clear();

    carte_.graphisme(rendu_);

    for (const auto& tour : tours_)
    {
        tour->render(rendu_, carte_.getTailleCase());
    }

    for (const auto& ennemi : ennemis_)
    {
        ennemi->render(rendu_);
    }

    for (const auto& projectile : projectiles_)
    {
        projectile.render(rendu_);
    }

    SDL_Rect curseurRect = {
        curseurX_ * carte_.getTailleCase(),
        curseurY_ * carte_.getTailleCase(),
        carte_.getTailleCase(),
        carte_.getTailleCase()
    };

    rendu_.setColor(
        COULEUR_CURSEUR_R,
        COULEUR_CURSEUR_G,
        COULEUR_CURSEUR_B,
        COULEUR_CURSEUR_A
    );

    SDL_RenderDrawRect(rendu_.getNativeRenderer(), &curseurRect);

    hud_.render(
        rendu_,
        joueur_,
        numeroVague_ - 1,
        estPause_
    );

    rendu_.present();
}

void Jeu::selectionnerTour(int typeTour)
{
    typeTourSelectionne_ = typeTour;

    if (typeTourSelectionne_ == 1)
    {
        std::cout << "Selection : Tour basique" << std::endl;
    }
    else if (typeTourSelectionne_ == 2)
    {
        std::cout << "Selection : Tour sniper" << std::endl;
    }
    else if (typeTourSelectionne_ == 3)
    {
        std::cout << "Selection : Tour canon" << std::endl;
    }
    else if (typeTourSelectionne_ == 4)
    {
        std::cout << "Selection : Tour glace" << std::endl;
    }
    else if (typeTourSelectionne_ == 5)
    {
        std::cout << "Selection : Tour anti-air" << std::endl;
    }
}

void Jeu::essayerAjouterTour()
{
    if (!carte_.estConstructible(curseurX_, curseurY_))
    {
        std::cout << "Impossible : construction seulement sur les cases @"
                  << std::endl;
        return;
    }

    if (tourExisteDeja(curseurX_, curseurY_))
    {
        std::cout << "Impossible : une tour existe deja ici"
                  << std::endl;
        return;
    }

    std::unique_ptr<Tour> nouvelleTour =
        TourFactory::creerTour(typeTourSelectionne_, curseurX_, curseurY_);

    if (!nouvelleTour)
    {
        return;
    }

    int cout = nouvelleTour->getCout();

    if (!joueur_.payer(cout))
    {
        std::cout << "Pas assez d'argent. Cout = "
                  << cout
                  << ", argent = "
                  << joueur_.getArgent()
                  << std::endl;
        return;
    }

    std::cout << "Tour ajoutee en "
              << curseurX_
              << ", "
              << curseurY_
              << " | Cout : "
              << cout
              << " | Argent restant : "
              << joueur_.getArgent()
              << std::endl;

    tours_.push_back(std::move(nouvelleTour));
}

bool Jeu::tourExisteDeja(int gridX, int gridY) const
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

void Jeu::afficherCommandes() const
{
    std::cout << "Commandes :" << std::endl;
    std::cout << "Fleches : deplacer le curseur" << std::endl;
    std::cout << "1 : tour basique" << std::endl;
    std::cout << "2 : tour sniper" << std::endl;
    std::cout << "3 : tour canon" << std::endl;
    std::cout << "4 : tour glace" << std::endl;
    std::cout << "5 : tour anti-air" << std::endl;
    std::cout << "A : placer une tour" << std::endl;
    std::cout << "ENTER : lancer une vague" << std::endl;
    std::cout << "SPACE : pause" << std::endl;
    std::cout << "ESC : quitter" << std::endl;
    std::cout << "Argent initial : " << joueur_.getArgent() << std::endl;
    std::cout << "Vies initiales : " << joueur_.getVies() << std::endl;
}