#pragma once

#include "../core/rendu.hpp"
#include "../core/joueur.hpp"
#include "../core/texture.hpp"

#include "../tours/type_tour.hpp"

#include <SDL2/SDL_ttf.h>

#include <memory>
#include <optional>
#include <string>

class Hud
{
private:
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font_;

public:
    Hud(const std::string& cheminPolice, int taillePolice);

    Hud(const Hud&) = delete;
    Hud& operator=(const Hud&) = delete;

    void render(
        Rendu& rendu,
        TextureManager& textureManager,
        const Joueur& joueur,
        int vagueActuelle,
        TypeTour typeTourSelectionne,
        bool dragTourActif,
        TypeTour dragTourType,
        bool estPause
    );

    std::optional<TypeTour> getPaletteTypeAt(int x, int y) const;
};