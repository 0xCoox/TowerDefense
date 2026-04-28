#include "projectile.hpp"

#include <SDL2/SDL.h>
#include <cmath>

Projectile::Projectile(float xDepart, float yDepart, float cibleX, float cibleY)
    : x_(xDepart),
      y_(yDepart),
      cibleX_(cibleX),
      cibleY_(cibleY),
      vitesse_(500.0f),
      termine_(false)
{
}

void Projectile::update(float dt)
{
    if (termine_)
    {
        return;
    }

    float dx = cibleX_ - x_;
    float dy = cibleY_ - y_;

    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < 4.0f)
    {
        termine_ = true;
        return;
    }

    float directionX = dx / distance;
    float directionY = dy / distance;

    float distanceAParcourir = vitesse_ * dt;

    if (distanceAParcourir >= distance)
    {
        x_ = cibleX_;
        y_ = cibleY_;
        termine_ = true;
        return;
    }

    x_ += directionX * distanceAParcourir;
    y_ += directionY * distanceAParcourir;
}

void Projectile::render(Rendu& rendu) const
{
    SDL_Rect rect = {
        static_cast<int>(x_ - 4),
        static_cast<int>(y_ - 4),
        8,
        8
    };

    rendu.setColor(255, 255, 0, 255);
    SDL_RenderFillRect(rendu.getNativeRenderer(), &rect);
}

bool Projectile::estTermine() const
{
    return termine_;
}