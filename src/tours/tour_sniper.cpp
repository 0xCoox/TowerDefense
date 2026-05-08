#include "tour_sniper.hpp"

#include <SDL2/SDL.h>

namespace
{
    constexpr int DEGAT = 60;
    constexpr float PORTEE = 260.0f;
    constexpr float DELAI_ATTAQUE = 1.5f;
    constexpr float VITESSE_PROJECTILE = 900.0f;
    constexpr int COUT = 80;
}

TourSniper::TourSniper(int gridX, int gridY)
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

    float centreX = gridX_ * tailleCase + tailleCase / 2.0f;
    float centreY = gridY_ * tailleCase + tailleCase / 2.0f;

    float angleRad = angle_ * (M_PI / 180.0f);

    float longueurCanon = tailleCase / 2.0f;
    float canonX = centreX + std::cos(angleRad) * longueurCanon;
    float canonY = centreY + std::sin(angleRad) * longueurCanon;

    rendu.setColor(255, 255, 255, 255); // Canon blanc
    SDL_RenderDrawLine(rendu.getNativeRenderer(), 
                       (int)centreX, (int)centreY, 
                       (int)canonX, (int)canonY);
}