#include "tour_basique.hpp"


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

void TourBasique::render(Rendu& rendu, int tailleCase) const
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