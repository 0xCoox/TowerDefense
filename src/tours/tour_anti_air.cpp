#include "tour_anti_air.hpp"

#include <SDL2/SDL.h>

TourAntiAir::TourAntiAir(int gridX, int gridY)
    : Tour(gridX, gridY, 25, 170.0f, 0.4f)
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