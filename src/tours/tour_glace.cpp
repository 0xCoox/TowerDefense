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


void TourGlace::render(Rendu& rendu, int tailleCase) const {
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
        SDL_RenderCopyEx(
            rendu.getNativeRenderer(),
            textureCanon_,
            &srcRect,        
            &dstRect,       
            angleCorrection,
            nullptr,         
            SDL_FLIP_NONE
        );
    }
}