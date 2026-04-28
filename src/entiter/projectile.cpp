#include "projectile.hpp"

#include <SDL2/SDL.h>

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
    float vitesse
)
    : x_(xDepart),
      y_(yDepart),
      idCible_(idCible),
      degat_(degat),
      vitesse_(vitesse),
      termine_(false)
{
}

void Projectile::update(
    float dt,
    std::vector<std::unique_ptr<Ennemi>>& ennemis
)
{
    if (termine_)
    {
        return;
    }

    auto it = std::find_if(
        ennemis.begin(),
        ennemis.end(),
        [this](const std::unique_ptr<Ennemi>& ennemi)
        {
            return ennemi &&
                   ennemi->getId() == idCible_ &&
                   !ennemi->estMort() &&
                   !ennemi->estArrive();
        }
    );

    if (it == ennemis.end())
    {
        termine_ = true;
        return;
    }

    Ennemi& cible = **it;

    float dx = cible.getX() - x_;
    float dy = cible.getY() - y_;

    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance <= DISTANCE_IMPACT)
    {
        cible.prendreDegat(degat_);
        termine_ = true;
        return;
    }

    float directionX = dx / distance;
    float directionY = dy / distance;

    float distanceAParcourir = vitesse_ * dt;

    if (distanceAParcourir >= distance)
    {
        x_ = cible.getX();
        y_ = cible.getY();

        cible.prendreDegat(degat_);
        termine_ = true;
        return;
    }

    x_ += directionX * distanceAParcourir;
    y_ += directionY * distanceAParcourir;
}

void Projectile::render(Rendu& rendu) const
{
    SDL_Rect rect = {
        static_cast<int>(x_ - TAILLE_PROJECTILE / 2),
        static_cast<int>(y_ - TAILLE_PROJECTILE / 2),
        TAILLE_PROJECTILE,
        TAILLE_PROJECTILE
    };

    rendu.setColor(
        COULEUR_PROJECTILE_R,
        COULEUR_PROJECTILE_G,
        COULEUR_PROJECTILE_B,
        COULEUR_PROJECTILE_A
    );

    SDL_RenderFillRect(rendu.getNativeRenderer(), &rect);
}

bool Projectile::estTermine() const
{
    return termine_;
}