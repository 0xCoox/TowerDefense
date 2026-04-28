#include "tour_sniper.hpp"

#include <SDL2/SDL.h>

TourSniper::TourSniper(int gridX, int gridY)
    : Tour(gridX, gridY, 60, 260.0f, 1.5f)
{
}

void TourSniper::render(Rendu& rendu, int tailleCase) const
{
    SDL_Rect rect = {
        gridX_ * tailleCase + 7,
        gridY_ * tailleCase + 7,
        tailleCase - 14,
        tailleCase - 14
    };

    rendu.setColor(0, 255, 100, 255);
    SDL_RenderFillRect(rendu.getNativeRenderer(), &rect);
}