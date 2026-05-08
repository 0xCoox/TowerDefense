#include "tour_sniper.hpp"
#include <SDL2/SDL.h>
#include <cmath>

namespace
{
    // On garde tes stats d'origine
    constexpr int DEGAT = 60;
    constexpr float PORTEE = 260.0f;
    constexpr float DELAI_ATTAQUE = 1.5f;
    constexpr float VITESSE_PROJECTILE = 900.0f;
    constexpr int COUT = 80;
}

TourSniper::TourSniper(int gridX, int gridY)
    : Tour(gridX, gridY, DEGAT, PORTEE, DELAI_ATTAQUE, VITESSE_PROJECTILE, COUT)
{
}

void TourSniper::render(Rendu& rendu, int tailleCase) const {
    SDL_Rect srcRect = { spriteX_, spriteY_, SPRITE_SIZE, SPRITE_SIZE };

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
    } else {
        rendu.setColor(255, 255, 0, 255); 
        SDL_RenderDrawRect(rendu.getNativeRenderer(), &dstRect);
    }
}