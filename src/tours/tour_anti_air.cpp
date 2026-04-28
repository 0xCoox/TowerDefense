#include "tour_anti_air.hpp"

#include <SDL2/SDL.h>

namespace
{
    constexpr int DEGAT = 25;
    constexpr float PORTEE = 170.0f;
    constexpr float DELAI_ATTAQUE = 0.4f;
    constexpr float VITESSE_PROJECTILE = 700.0f;
    constexpr int COUT = 42;
}

TourAntiAir::TourAntiAir(int gridX, int gridY)
    : Tour(
          gridX,
          gridY,
          DEGAT,
          PORTEE,
          DELAI_ATTAQUE,
          VITESSE_PROJECTILE,
          COUT
      )
{
}

void TourAntiAir::render(Rendu& rendu, int tailleCase) const
{
    SDL_Rect rect = {
        gridX_ * tailleCase + 4,
        gridY_ * tailleCase + 4,
        tailleCase - 8,
        tailleCase - 8
    };

    rendu.setColor(180, 80, 255, 255);
    SDL_RenderFillRect(rendu.getNativeRenderer(), &rect);
}

bool TourAntiAir::peutCibler(const Ennemi& ennemi) const
{
    return ennemi.estVolant();
}