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

void TourBasique::render(Rendu& rendu, int tailleCase) const {
    const int SIZE = 96; 

    int currentSpriteX = (niveau_ - 1) * SIZE;    
    SDL_Rect srcRect = { currentSpriteX, spriteY_, SPRITE_SIZE, SPRITE_SIZE };

    SDL_Rect dstRect = { 
        gridX_ * tailleCase, 
        gridY_ * tailleCase, 
        tailleCase, 
        tailleCase 
    };

    if (textureCanon_ != nullptr) {
        float angleCorrection = angle_ + 90.0f;
        rendu.renderCopyEx(
            textureCanon_,
            &srcRect,
            &dstRect,
            angleCorrection,
            nullptr,
            SDL_FLIP_NONE
        );
    } else {
        rendu.setColor(255, 255, 0, 255); 
        rendu.drawRect(dstRect);
    }
}