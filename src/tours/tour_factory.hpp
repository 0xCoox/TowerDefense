#pragma once

#include "tour.hpp"
#include "type_tour.hpp"
#include "../core/texture.hpp"

#include <memory>

class TourFactory
{
public:
    static std::unique_ptr<Tour> creerTour(
        TypeTour typeTour,
        int gridX,
        int gridY,
        TextureManager& tm
    );
};