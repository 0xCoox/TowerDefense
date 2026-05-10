#include "tour_glace.hpp"


namespace
{
    constexpr int DEGAT = 5;
    constexpr float PORTEE = 110.0f;
    constexpr float DELAI_ATTAQUE = 0.7f;
    constexpr float VITESSE_PROJECTILE = 400.0f;
    constexpr int COUT = 80;
    constexpr float COEFF_SLOW = 0.5f;
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
    ralentissement_ = COEFF_SLOW;
}


void TourGlace::render(Rendu& rendu, int tailleCase) const
{
    constexpr int SIZE = 96;

    int currentSpriteX = (niveau_ - 1) * SIZE;

    int dstX = gridX_ * tailleCase;
    int dstY = gridY_ * tailleCase;

    if (textureCanon_ != nullptr)
    {
        double angleCorrection = angle_ + 90.0;

        rendu.renderCopyEx(
            textureCanon_,
            currentSpriteX,
            spriteY_,
            SPRITE_SIZE,
            SPRITE_SIZE,
            dstX,
            dstY,
            tailleCase,
            tailleCase,
            angleCorrection,
            tailleCase / 2,
            tailleCase / 2
        );
    }
    else
    {
        rendu.setColor(100, 150, 255, 255);

        rendu.drawRect(
            dstX,
            dstY,
            tailleCase,
            tailleCase
        );
    }
}