#pragma once

#include "../core/rendu.hpp"
#include "../core/joueur.hpp"

#include <SDL2/SDL_ttf.h>

#include <memory>
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
        const Joueur& joueur,
        int vagueActuelle,
        bool estPause
    );
};