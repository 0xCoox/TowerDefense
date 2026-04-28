#include "tour_canon.hpp"

#include <SDL2/SDL.h>

namespace
{
    constexpr int DEGAT = 35;
    constexpr float PORTEE = 100.0f;
    constexpr float DELAI_ATTAQUE = 1.0f;
    constexpr float VITESSE_PROJECTILE = 300.0f;
    constexpr int COUT = 60;
}

TourCanon::TourCanon(int gridX, int gridY)
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

void TourCanon::render(Rendu& rendu, int tailleCase) const
{
    SDL_Rect rect = {
        gridX_ * tailleCase + 3,
        gridY_ * tailleCase + 3,
        tailleCase - 6,
        tailleCase - 6
    };

    rendu.setColor(255, 130, 0, 255);
    SDL_RenderFillRect(rendu.getNativeRenderer(), &rect);
}