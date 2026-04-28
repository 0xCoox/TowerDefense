#pragma once

#include "tour.hpp"

#include <memory>

class TourFactory
{
public:
    static std::unique_ptr<Tour> creerTour(int typeTour, int gridX, int gridY);
};