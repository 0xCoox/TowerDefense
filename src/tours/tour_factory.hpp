#pragma once

#include "tour.hpp"
#include "../core/texture.hpp"

#include <memory>

class TourFactory
{
public:
    static std::unique_ptr<Tour> creerTour(int typeTour, int gridX, int gridY, TextureManager& tm);
};