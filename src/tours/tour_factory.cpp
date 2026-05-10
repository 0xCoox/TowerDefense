#include "tour_factory.hpp"
#include "tour_basique.hpp"
#include "tour_sniper.hpp"
#include "tour_canon.hpp"
#include "tour_glace.hpp"
#include "tour_anti_air.hpp"


std::unique_ptr<Tour> TourFactory::creerTour(
    TypeTour typeTour,
    int gridX,
    int gridY,
    TextureManager& tm
)
{
    std::unique_ptr<Tour> nouvelleTour = nullptr;
    SDL_Texture* tex = tm.get("weapons_purple");
    SDL_Texture* tex_freeze = tm.get("weapons_blue");

    switch (typeTour)
    {
        case TypeTour::Basique:
            nouvelleTour = std::make_unique<TourBasique>(gridX, gridY);
            if (nouvelleTour)
            {
                nouvelleTour->setCanonStyle(tex, 0, 0);
            }
            break;

        case TypeTour::Sniper:
            nouvelleTour = std::make_unique<TourSniper>(gridX, gridY);
            if (nouvelleTour)
            {
                nouvelleTour->setCanonStyle(tex, 0, 1);
            }
            break;

        case TypeTour::Canon:
            nouvelleTour = std::make_unique<TourCanon>(gridX, gridY);
            if (nouvelleTour)
            {
                nouvelleTour->setCanonStyle(tex, 0, 3);
            }
            break;

        case TypeTour::Glace:
            nouvelleTour = std::make_unique<TourGlace>(gridX, gridY);
            if (nouvelleTour)
            {
                nouvelleTour->setCanonStyle(tex_freeze, 0, 1);
            }
            break;

        case TypeTour::AntiAir:
            nouvelleTour = std::make_unique<TourAntiAir>(gridX, gridY);
            if (nouvelleTour)
            {
                nouvelleTour->setCanonStyle(tex, 0, 2);
            }
            break;
    }

    return nouvelleTour;
}