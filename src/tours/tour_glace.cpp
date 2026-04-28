#include "tour_glace.hpp"

#include <SDL2/SDL.h>

TourGlace::TourGlace(int gridX, int gridY)
    : Tour(gridX, gridY, 5, 110.0f, 0.7f)
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