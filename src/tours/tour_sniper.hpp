#pragma once

#include "tour.hpp"

class TourSniper : public Tour
{
public:
    TourSniper(int gridX, int gridY);

    void render(Rendu& rendu, int tailleCase) const override;
};