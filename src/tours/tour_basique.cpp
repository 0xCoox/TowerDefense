#include "tour_basique.hpp"

#include <SDL2/SDL.h>

namespace
{
    constexpr int DEGAT = 15;
    constexpr float PORTEE = 120.0f;
    constexpr float DELAI_ATTAQUE = 0.5f;
    constexpr float VITESSE_PROJECTILE = 450.0f;
    constexpr int COUT = 48;
}

TourBasique::TourBasique(int gridX, int gridY)
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

void TourBasique::render(Rendu& rendu, int tailleCase) const
{
    SDL_Rect rect = {
        gridX_ * tailleCase + 5,
        gridY_ * tailleCase + 5,
        tailleCase - 10,
        tailleCase - 10
    };

    rendu.setColor(0, 120, 255, 255);
    SDL_RenderFillRect(rendu.getNativeRenderer(), &rect);
}