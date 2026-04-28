#include "hud.hpp"

#include <SDL2/SDL.h>

#include <stdexcept>
#include <string>

namespace
{
    constexpr int LARGEUR_FENETRE = 720;
    constexpr int HAUTEUR_FENETRE = 720;

    constexpr int MARGE = 15;

    constexpr int FOND_LARGEUR = 560;
    constexpr int FOND_HAUTEUR = 45;

    constexpr int FOND_X = MARGE;
    constexpr int FOND_Y = HAUTEUR_FENETRE - FOND_HAUTEUR - MARGE;

    constexpr int POSITION_X = FOND_X + 7;
    constexpr int POSITION_Y = FOND_Y + 10;

    constexpr Uint8 TEXTE_R = 255;
    constexpr Uint8 TEXTE_G = 255;
    constexpr Uint8 TEXTE_B = 255;
    constexpr Uint8 TEXTE_A = 255;

    constexpr Uint8 FOND_R = 0;
    constexpr Uint8 FOND_G = 0;
    constexpr Uint8 FOND_B = 0;
    constexpr Uint8 FOND_A = 180;
}

Hud::Hud(const std::string& cheminPolice, int taillePolice)
    : font_(nullptr, &TTF_CloseFont)
{
    TTF_Font* rawFont = TTF_OpenFont(
        cheminPolice.c_str(),
        taillePolice
    );

    if (rawFont == nullptr)
    {
        throw std::runtime_error(
            "Impossible de charger la police : " +
            cheminPolice +
            " | Erreur TTF : " +
            std::string(TTF_GetError())
        );
    }

    font_.reset(rawFont);
}

void Hud::render(
    Rendu& rendu,
    const Joueur& joueur,
    int vagueActuelle,
    bool estPause
)
{
    SDL_Rect fond = {
        FOND_X,
        FOND_Y,
        FOND_LARGEUR,
        FOND_HAUTEUR
    };

    rendu.setColor(FOND_R, FOND_G, FOND_B, FOND_A);
    SDL_RenderFillRect(rendu.getNativeRenderer(), &fond);

    std::string texte =
        "Argent : " + std::to_string(joueur.getArgent()) +
        "   |   Vies : " + std::to_string(joueur.getVies()) +
        "   |   Vague : " + std::to_string(vagueActuelle);

    if (estPause)
    {
        texte += "   |   PAUSE";
    }

    SDL_Color couleurTexte = {
        TEXTE_R,
        TEXTE_G,
        TEXTE_B,
        TEXTE_A
    };

    rendu.dessinerTexte(
        font_.get(),
        texte,
        POSITION_X,
        POSITION_Y,
        couleurTexte
    );
}