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
    SDL_Texture* tex_freeze = tm.get("weapons_blue");

    if (typeTour == 1) {
        nouvelleTour = std::make_unique<TourBasique>(gridX, gridY);
        if (nouvelleTour) nouvelleTour->setCanonStyle(tex, 0, 0); // Canon VIOLET Simple
    }
    else if (typeTour == 2) {
        nouvelleTour = std::make_unique<TourSniper>(gridX, gridY);
        if (nouvelleTour) nouvelleTour->setCanonStyle(tex, 0, 1); // Canon VILET SNIPER
    }
    else if (typeTour == 3) {
        nouvelleTour = std::make_unique<TourCanon>(gridX, gridY);
        if (nouvelleTour) nouvelleTour->setCanonStyle(tex, 0, 3); // GROS GROS Canon
    }
    else if (typeTour == 4) {
        nouvelleTour = std::make_unique<TourGlace>(gridX, gridY);
        if (nouvelleTour) nouvelleTour->setCanonStyle(tex_freeze, 0, 1); // Canon Bleu SNIPER
    }
    else if (typeTour == 5) {
        nouvelleTour = std::make_unique<TourAntiAir>(gridX, gridY);
        if (nouvelleTour) nouvelleTour->setCanonStyle(tex, 0, 2); // Missile AntiAIR VIOLET
    }

    return nouvelleTour;
}