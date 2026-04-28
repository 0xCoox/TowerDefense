#pragma once

#include "tour.hpp"

class TourBasique : public Tour
{
public:
    TourBasique(int gridX, int gridY);

    void render(Rendu& rendu, int tailleCase) const override;
};