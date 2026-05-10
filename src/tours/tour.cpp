#include "tour.hpp"

#include <cmath>

Tour::Tour(
    int gridX,
    int gridY,
    int degat,
    float portee,
    float delaiAttaque,
    float vitesseProjectile,
    int cout
)
    : gridX_(gridX),
      gridY_(gridY),
      degat_(degat),
      portee_(portee),
      delaiAttaque_(delaiAttaque),
      timerAttaque_(0.0f),
      vitesseProjectile_(vitesseProjectile),
      ralentissement_(1.0f), 
      rayonSplash_(0.0f),                 
      cout_(cout),
      angle_(0.0f),
      idCibleVerrouille_(-1), 
      niveau_(1),
      niveauMax_(4),       
      totalInvesti_(cout) 
{
}

void Tour::update(
    float dt,
    std::vector<std::unique_ptr<Ennemi>>& ennemis,
    std::vector<Projectile>& projectiles,
    int tailleCase
)
{
    // 1. Gestion du timer d'attaque
    if (timerAttaque_ > 0.0f)
    {
        timerAttaque_ -= dt;
    }

    auto it = std::find_if(ennemis.begin(), ennemis.end(), [this, tailleCase](const std::unique_ptr<Ennemi>& e) {
        return e && e->getId() == idCibleVerrouille_ && 
               !e->estMort() && !e->estArrive() && estDansPortee(*e, tailleCase);
    });

    std::optional<std::size_t> indexCible;

    if (it != ennemis.end()) 
    {
        // Cible toujours valide
        indexCible = std::distance(ennemis.begin(), it);
    } 
    else 
    {
        // la cible est morte ou hors de portée on relance une recherche
        indexCible = trouverIndexCible(ennemis, tailleCase);
        
        if (indexCible.has_value()) 
        {
            // on se souvient de l'id pour la suite 
            idCibleVerrouille_ = ennemis[indexCible.value()]->getId();
        } 
        else 
        {
            //rien ne se passe
            idCibleVerrouille_ = -1;
            return; 
        }
    }

    // calcul de l'angle
    Ennemi& cible = *ennemis.at(indexCible.value());

    float centreTourX = gridX_ * tailleCase + tailleCase / 2.0f;
    float centreTourY = gridY_ * tailleCase + tailleCase / 2.0f;

    float dx = cible.getX() - centreTourX;
    float dy = cible.getY() - centreTourY;

    // angle instantané
    float angleCible = std::atan2(dy, dx) * (180.0f / M_PI);

    // on evite les rotations instatanés
    float diff = angleCible - angle_;
    while (diff > 180)  diff -= 360;
    while (diff < -180) diff += 360;

    // Vitesse de rotation 
    angle_ += diff * 10.0f * dt;
    if (timerAttaque_ <= 0.0f)
    {
        creerProjectileVers(cible, projectiles, tailleCase);
        timerAttaque_ = delaiAttaque_;
    }
}

void Tour::render(Rendu& rendu, int tailleCase) const
{
    if (textureBase_)
    {
        SDL_Rect rect = {
            gridX_ * tailleCase,
            gridY_ * tailleCase,
            tailleCase,
            tailleCase
        };

        rendu.renderCopy(textureBase_, nullptr, &rect);
    }
}

bool Tour::peutCibler(const Ennemi& ennemi) const
{
    (void)ennemi;
    return true;
}

bool Tour::estDansPortee(const Ennemi& ennemi, int tailleCase) const
{
    float centreTourX = gridX_ * tailleCase + tailleCase / 2.0f;
    float centreTourY = gridY_ * tailleCase + tailleCase / 2.0f;

    float dx = ennemi.getX() - centreTourX;
    float dy = ennemi.getY() - centreTourY;

    float distance = std::sqrt(dx * dx + dy * dy);

    return distance <= portee_;
}

std::optional<std::size_t> Tour::trouverIndexCible(
    const std::vector<std::unique_ptr<Ennemi>>& ennemis,
    int tailleCase
) const
{
    std::optional<std::size_t> meilleurIndex;
    float meilleureProgression = -1.0f;

    for (std::size_t i = 0; i < ennemis.size(); i++)
    {
        const std::unique_ptr<Ennemi>& ennemi = ennemis[i];

        if (!ennemi)
        {
            continue;
        }

        if (ennemi->estMort())
        {
            continue;
        }

        if (ennemi->estArrive())
        {
            continue;
        }

        if (!peutCibler(*ennemi))
        {
            continue;
        }

        if (!estDansPortee(*ennemi, tailleCase))
        {
            continue;
        }

        float progression = ennemi->getProgressionChemin();

        if (progression > meilleureProgression)
        {
            meilleureProgression = progression;
            meilleurIndex = i;
        }
    }

    return meilleurIndex;
}

void Tour::creerProjectileVers(
    const Ennemi& ennemi,
    std::vector<Projectile>& projectiles,
    int tailleCase
) const
{
    float centreTourX = gridX_ * tailleCase + tailleCase / 2.0f;
    float centreTourY = gridY_ * tailleCase + tailleCase / 2.0f;

    projectiles.emplace_back(
        centreTourX,
        centreTourY,
        ennemi.getId(),
        degat_,
        ralentissement_, 
        rayonSplash_,
        vitesseProjectile_
    );
}

bool Tour::ameliorer()
{
    if (!peutAmeliorer())
    {
        return false;
    }

    int coutAmelioration = getCoutAmelioration();

    niveau_++;
    totalInvesti_ += coutAmelioration;

    degat_ = static_cast<int>(degat_ * 1.30f);
    portee_ *= 1.10f;
    delaiAttaque_ *= 0.90f;
    vitesseProjectile_ *= 1.05f;

    return true;
}

int Tour::getCoutAmelioration() const
{
    if (!peutAmeliorer())
    {
        return 0;
    }

    return (cout_ / 2) * niveau_;
}
