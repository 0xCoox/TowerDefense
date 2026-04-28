#include "tour_basique.hpp"

#include <SDL2/SDL.h>

TourBasique::TourBasique(int gridX, int gridY)
    : Tour(gridX, gridY, 15, 120.0f, 0.5f)
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