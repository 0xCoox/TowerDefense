#include "tour_factory.hpp"
#include "tour_basique.hpp"
#include "tour_sniper.hpp"
#include "tour_canon.hpp"
#include "tour_glace.hpp"
#include "tour_anti_air.hpp"


std::unique_ptr<Tour> TourFactory::creerTour(int typeTour, int gridX, int gridY, TextureManager& tm)
{
    std::unique_ptr<Tour> nouvelleTour = nullptr;
    SDL_Texture* tex = tm.get("weapons_purple");
    if (typeTour == 1) {
        nouvelleTour = std::make_unique<TourBasique>(gridX, gridY);
        if (nouvelleTour) nouvelleTour->setCanonStyle(tex, 0, 0); // Canon simple
    }
    else if (typeTour == 2) {
        nouvelleTour = std::make_unique<TourSniper>(gridX, gridY);
        if (nouvelleTour) nouvelleTour->setCanonStyle(tex, 0, 1); // Canon Plasma
    }
    else if (typeTour == 3) {
        nouvelleTour = std::make_unique<TourCanon>(gridX, gridY);
        if (nouvelleTour) nouvelleTour->setCanonStyle(tex, 0, 3); // Gros Canon
    }
    else if (typeTour == 4) {
        nouvelleTour = std::make_unique<TourGlace>(gridX, gridY);
        if (nouvelleTour) nouvelleTour->setCanonStyle(tex, 3, 1); // Canon Énergie
    }
    else if (typeTour == 5) {
        nouvelleTour = std::make_unique<TourAntiAir>(gridX, gridY);
        if (nouvelleTour) nouvelleTour->setCanonStyle(tex, 0, 2); // Missiles
    }

    return nouvelleTour;
}