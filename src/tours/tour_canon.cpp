#include "tour_canon.hpp"


namespace
{
    constexpr int DEGAT = 35;
    constexpr float PORTEE = 100.0f;
    constexpr float DELAI_ATTAQUE = 1.0f;
    constexpr float VITESSE_PROJECTILE = 300.0f;
    constexpr int COUT = 60;
}

TourCanon::TourCanon(int gridX, int gridY)
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
    rayonSplash_ = 40.0f; 
}

void TourCanon::render(Rendu& rendu, int tailleCase) const
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
        rendu.setColor(255, 255, 0, 255);

        rendu.drawRect(
            dstX,
            dstY,
            tailleCase,
            tailleCase
        );
    }
}