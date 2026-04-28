#pragma once

#include "tour.hpp"

class TourGlace : public Tour
{
public:
    TourGlace(int gridX, int gridY);

    void render(Rendu& rendu, int tailleCase) const override;
};