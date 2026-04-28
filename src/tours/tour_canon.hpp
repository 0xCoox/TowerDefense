#pragma once

#include "tour.hpp"

class TourCanon : public Tour
{
public:
    TourCanon(int gridX, int gridY);

    void render(Rendu& rendu, int tailleCase) const override;
};