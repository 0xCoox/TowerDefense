#include "hud.hpp"

#include "game_config.hpp"
#include "../tours/tour_factory.hpp"

#include <SDL2/SDL.h>

#include <stdexcept>
#include <string>

#include <array>

namespace
{
    constexpr int MARGE = 15;

    constexpr int FOND_LARGEUR = 560;
    constexpr int FOND_HAUTEUR = 45;

    constexpr int FOND_X = MARGE;
    constexpr int FOND_Y = GameConfig::HAUTEUR_FENETRE - FOND_HAUTEUR - MARGE;

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

    constexpr int PALETTE_X = GameConfig::LARGEUR_MAP + 25;
    constexpr int PALETTE_Y = 320;
    constexpr int PALETTE_TAILLE = 48;
    constexpr int PALETTE_GAP = 10;

    constexpr int SPRITE_SIZE = 96;

    struct PaletteDef
    {
        TypeTour type;
        const char* textureId;
        int spriteRow;
    };

    struct Rect
    {
        int x;
        int y;
        int w;
        int h;
    };

    constexpr std::array<PaletteDef, 5> PALETTE_DEFS = {
        PaletteDef{TypeTour::Basique, "weapons_purple", 0},
        PaletteDef{TypeTour::Sniper, "weapons_purple", 1},
        PaletteDef{TypeTour::Canon, "weapons_purple", 3},
        PaletteDef{TypeTour::Glace, "weapons_blue", 1},
        PaletteDef{TypeTour::AntiAir, "weapons_purple", 2}
    };

    Rect getPaletteRect(std::size_t index)
    {
        return Rect{
            PALETTE_X,
            PALETTE_Y + static_cast<int>(index) * (PALETTE_TAILLE + PALETTE_GAP),
            PALETTE_TAILLE,
            PALETTE_TAILLE
        };
    }

    bool pointDansRect(int x, int y, const Rect& rect)
    {
        return x >= rect.x && x < (rect.x + rect.w) &&
               y >= rect.y && y < (rect.y + rect.h);
    }
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
    TextureManager& textureManager,
    const Joueur& joueur,
    int vagueActuelle,
    TypeTour typeTourSelectionne,
    bool dragTourActif,
    TypeTour dragTourType,
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
    rendu.fillRect(fond);

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

    for (std::size_t i = 0; i < PALETTE_DEFS.size(); ++i)
    {
        const PaletteDef& def = PALETTE_DEFS[i];
        Rect rect = getPaletteRect(i);

        bool actif = (def.type == typeTourSelectionne);
        bool drag = dragTourActif && (def.type == dragTourType);

        if (drag)
        {
            rendu.setColor(255, 220, 0, 255);
        }
        else if (actif)
        {
            rendu.setColor(255, 255, 255, 255);
        }
        else
        {
            rendu.setColor(120, 120, 120, 255);
        }

        rendu.drawRect(rect.x, rect.y, rect.w, rect.h);

        SDL_Texture* texture = textureManager.get(def.textureId);
        if (texture)
        {
            rendu.renderCopy(
                texture,
                0,
                def.spriteRow * SPRITE_SIZE,
                SPRITE_SIZE,
                SPRITE_SIZE,
                rect.x,
                rect.y,
                rect.w,
                rect.h
            );
        }

        std::unique_ptr<Tour> preview =
            TourFactory::creerTour(def.type, 0, 0, textureManager);
        if (preview)
        {
            int cout = preview->getCout();
            std::string prix = std::to_string(cout);
            SDL_Color couleurPrix = {220, 220, 220, 255};

            rendu.dessinerTexte(
                font_.get(),
                prix,
                rect.x + rect.w + 6,
                rect.y + 12,
                couleurPrix
            );
        }
    }
}

std::optional<TypeTour> Hud::getPaletteTypeAt(int x, int y) const
{
    for (std::size_t i = 0; i < PALETTE_DEFS.size(); ++i)
    {
        Rect rect = getPaletteRect(i);
        if (pointDansRect(x, y, rect))
        {
            return PALETTE_DEFS[i].type;
        }
    }

    return std::nullopt;
}