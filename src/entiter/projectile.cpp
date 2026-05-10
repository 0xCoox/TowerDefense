#include "projectile.hpp"


#include <algorithm>
#include <cmath>

namespace
{
    constexpr float DISTANCE_IMPACT = 6.0f;

    constexpr int TAILLE_PROJECTILE = 8;

    constexpr Uint8 COULEUR_PROJECTILE_R = 255;
    constexpr Uint8 COULEUR_PROJECTILE_G = 255;
    constexpr Uint8 COULEUR_PROJECTILE_B = 0;
    constexpr Uint8 COULEUR_PROJECTILE_A = 255;
}

Projectile::Projectile(
    float xDepart,
    float yDepart,
    int idCible,
    int degat,
    float ralentissement,
    float rayonSplash,
    float vitesse
)
    : x_(xDepart),
      y_(yDepart),
      idCible_(idCible),
      degat_(degat),
      ralentissement_(ralentissement),
      rayonSplash_(rayonSplash),
      vitesse_(vitesse),
      termine_(false)
{
}

void Projectile::update(float dt, std::vector<std::unique_ptr<Ennemi>>& ennemis)
{
    if (termine_) return;

    auto it = std::find_if(ennemis.begin(), ennemis.end(), [this](const std::unique_ptr<Ennemi>& e) {
        return e && e->getId() == idCible_ && !e->estMort() && !e->estArrive();
    });

    if (it == ennemis.end()) {
        termine_ = true;
        return;
    }

    Ennemi& cible = *(it->get()); 

    float dx = cible.getX() - x_;
    float dy = cible.getY() - y_;
    float distance = std::sqrt(dx * dx + dy * dy);
    float deplacement = vitesse_ * dt;
    if (distance <= DISTANCE_IMPACT || deplacement >= distance) 
    {
        float impactX = cible.getX();
        float impactY = cible.getY();

        if (rayonSplash_ > 0.0f) 
        {
            float rayonCarre = rayonSplash_ * rayonSplash_;

            for (const auto& ennemiPtr : ennemis) 
            {
                if (ennemiPtr && !ennemiPtr->estMort()) 
                {
                    float diffX = ennemiPtr->getX() - impactX;
                    float diffY = ennemiPtr->getY() - impactY;
                    float distEnnemiCarre = (diffX * diffX) + (diffY * diffY);

                    if (distEnnemiCarre <= rayonCarre) 
                    {
                        ennemiPtr->prendreDegat(degat_);
                    }
                }
            }
        } 
        else 
        {
            cible.prendreDegat(degat_);
            cible.appliquerRalentissement(ralentissement_, 4.0f);
        }

        termine_ = true;
    } 
    else 
    {
        x_ += (dx / distance) * deplacement;
        y_ += (dy / distance) * deplacement;
    }
}


void Projectile::render(Rendu& rendu) const
{
    int rectX = static_cast<int>(x_ - TAILLE_PROJECTILE / 2);
    int rectY = static_cast<int>(y_ - TAILLE_PROJECTILE / 2);

    // choisit couleur projectiles
    if (ralentissement_ < 1.0f)
    {
        rendu.setColor(100, 150, 255, 255);
    }
    else if (rayonSplash_ > 0.0f)
    {
        rendu.setColor(255, 100, 0, 255);
    }
    else
    {
        rendu.setColor(
            COULEUR_PROJECTILE_R,
            COULEUR_PROJECTILE_G,
            COULEUR_PROJECTILE_B,
            COULEUR_PROJECTILE_A
        );
    }

    rendu.fillRect(
        rectX,
        rectY,
        TAILLE_PROJECTILE,
        TAILLE_PROJECTILE
    );
}