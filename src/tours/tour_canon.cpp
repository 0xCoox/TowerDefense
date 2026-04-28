#include "tour_canon.hpp"

#include <SDL2/SDL.h>

TourCanon::TourCanon(int gridX, int gridY)
    : Tour(gridX, gridY, 35, 100.0f, 1.0f)
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