#include "tour_factory.hpp"
#include "tour_basique.hpp"
#include "tour_sniper.hpp"
#include "tour_canon.hpp"
#include "tour_glace.hpp"
#include "tour_anti_air.hpp"

std::unique_ptr<Tour> TourFactory::creerTour(int typeTour, int gridX, int gridY)
{
    if (typeTour == 1)
    {
        return std::make_unique<TourBasique>(gridX, gridY);
    }

    if (typeTour == 2)
    {
        return std::make_unique<TourSniper>(gridX, gridY);
    }

    if (typeTour == 3)
    {
        return std::make_unique<TourCanon>(gridX, gridY);
    }

    if (typeTour == 4)
    {
        return std::make_unique<TourGlace>(gridX, gridY);
    }

    if (typeTour == 5)
    {
        return std::make_unique<TourAntiAir>(gridX, gridY);
    }

    return nullptr;
}