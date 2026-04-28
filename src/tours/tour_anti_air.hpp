#pragma once

#include "tour.hpp"

class TourAntiAir : public Tour
{
public:
    TourAntiAir(int gridX, int gridY);

    void render(Rendu& rendu, int tailleCase) const override;
    bool peutCibler(const Ennemi& ennemi) const override;
};