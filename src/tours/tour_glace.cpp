#include "tour_glace.hpp"

#include <SDL2/SDL.h>

namespace
{
    constexpr int DEGAT = 5;
    constexpr float PORTEE = 110.0f;
    constexpr float DELAI_ATTAQUE = 0.7f;
    constexpr float VITESSE_PROJECTILE = 400.0f;
    constexpr int COUT = 80;
}

TourGlace::TourGlace(int gridX, int gridY)
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

void TourGlace::render(Rendu& rendu, int tailleCase) const
{
    SDL_Rect rect = {
        gridX_ * tailleCase + 5,
        gridY_ * tailleCase + 5,
        tailleCase - 10,
        tailleCase - 10
    };

    rendu.setColor(0, 220, 255, 255);
    SDL_RenderFillRect(rendu.getNativeRenderer(), &rect);
}