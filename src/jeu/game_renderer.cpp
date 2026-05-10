#include "game_renderer.hpp"

#include "game_config.hpp"
#include "../tours/tour_factory.hpp"

#include <array>
#include <cmath>

namespace
{
    constexpr int COULEUR_FOND_R = 0;
    constexpr int COULEUR_FOND_G = 0;
    constexpr int COULEUR_FOND_B = 0;
    constexpr int COULEUR_FOND_A = 255;

    constexpr int COULEUR_CURSEUR_R = 255;
    constexpr int COULEUR_CURSEUR_G = 0;
    constexpr int COULEUR_CURSEUR_B = 0;
    constexpr int COULEUR_CURSEUR_A = 255;

    constexpr int SPRITE_SIZE = 96;

    struct PaletteDef
    {
        TypeTour type;
        const char* textureId;
        int spriteRow;
    };

    constexpr std::array<PaletteDef, 5> PALETTE_DEFS = {
        PaletteDef{TypeTour::Basique, "weapons_purple", 0},
        PaletteDef{TypeTour::Sniper, "weapons_purple", 1},
        PaletteDef{TypeTour::Canon, "weapons_purple", 3},
        PaletteDef{TypeTour::Glace, "weapons_blue", 1},
        PaletteDef{TypeTour::AntiAir, "weapons_purple", 2}
    };
}

void GameRenderer::dessiner(
    Rendu& rendu,
    Carte& carte,
    TextureManager& textureManager,
    BouttonManager& guiManager,
    Hud& hud,
    Joueur& joueur,
    const std::vector<std::unique_ptr<Tour>>& tours,
    const std::vector<std::unique_ptr<Ennemi>>& ennemis,
    const std::vector<Projectile>& projectiles,
    int curseurX,
    int curseurY,
    int sourisX,
    int sourisY,
    int numeroVague,
    TypeTour typeTourSelectionne,
    bool dragTourActif,
    TypeTour dragTourType,
    bool estPause,
    bool afficherPorteePlacement
)
{
    rendu.setColor(COULEUR_FOND_R, COULEUR_FOND_G, COULEUR_FOND_B, COULEUR_FOND_A);
    rendu.clear();

    SDL_Texture* texMap = textureManager.get("map_sprite");
    SDL_Texture* texBase = textureManager.get("base_tour");

    carte.graphisme(rendu, texMap, texBase);

    dessinerPorteeAuCurseur(
        rendu,
        carte,
        textureManager,
        tours,
        curseurX,
        curseurY,
        typeTourSelectionne,
        afficherPorteePlacement
    );

    if (dragTourActif)
    {
        dessinerApercuDrag(
            rendu,
            carte,
            textureManager,
            tours,
            sourisX,
            sourisY,
            dragTourType
        );
    }

    for (const auto& tour : tours)
    {
        tour->render(rendu, carte.getTailleCase());
    }

    for (const auto& ennemi : ennemis)
    {
        ennemi->render(rendu);
    }

    for (const auto& projectile : projectiles)
    {
        projectile.render(rendu);
    }

    int curseurRectX = curseurX * carte.getTailleCase();
    int curseurRectY = curseurY * carte.getTailleCase();
    int curseurRectTaille = carte.getTailleCase();

    rendu.setColor(
        COULEUR_CURSEUR_R,
        COULEUR_CURSEUR_G,
        COULEUR_CURSEUR_B,
        COULEUR_CURSEUR_A
    );

    rendu.drawRect(
        curseurRectX,
        curseurRectY,
        curseurRectTaille,
        curseurRectTaille
    );

    int sidebarRectX = GameConfig::LARGEUR_MAP;
    int sidebarRectY = 0;
    int sidebarRectW = GameConfig::LARGEUR_SIDEBAR;
    int sidebarRectH = GameConfig::HAUTEUR_FENETRE;

    rendu.setColor(40, 40, 40, 255);
    rendu.fillRect(sidebarRectX, sidebarRectY, sidebarRectW, sidebarRectH);

    guiManager.render(rendu);

    hud.render(
        rendu,
        textureManager,
        joueur,
        numeroVague - 1,
        typeTourSelectionne,
        dragTourActif,
        dragTourType,
        estPause
    );

    rendu.present();
}

float GameRenderer::getPorteeTourSelectionnee(
    TypeTour typeTourSelectionne,
    int curseurX,
    int curseurY,
    TextureManager& textureManager
)
{
    std::unique_ptr<Tour> tourPreview =
        TourFactory::creerTour(
            typeTourSelectionne,
            curseurX,
            curseurY,
            textureManager
        );

    if (!tourPreview)
    {
        return 0.0f;
    }

    return tourPreview->getPortee();
}

void GameRenderer::dessinerPorteeAuCurseur(
    Rendu& rendu,
    Carte& carte,
    TextureManager& textureManager,
    const std::vector<std::unique_ptr<Tour>>& tours,
    int curseurX,
    int curseurY,
    TypeTour typeTourSelectionne,
    bool afficherPorteePlacement
)
{
    int indexTour = trouverIndexTour(tours, curseurX, curseurY);

    if (indexTour != -1)
    {
        float portee = tours[indexTour]->getPortee();

        dessinerCerclePortee(
            rendu,
            carte,
            curseurX,
            curseurY,
            portee,
            80,
            160,
            255,
            45
        );

        return;
    }

    if (!afficherPorteePlacement)
    {
        return;
    }

    bool caseConstructibleVide =
        carte.estConstructible(curseurX, curseurY) &&
        trouverIndexTour(tours, curseurX, curseurY) == -1;

    if (!caseConstructibleVide)
    {
        return;
    }

    float porteePreview = getPorteeTourSelectionnee(
        typeTourSelectionne,
        curseurX,
        curseurY,
        textureManager
    );

    if (porteePreview <= 0.0f)
    {
        return;
    }

    dessinerCerclePortee(
        rendu,
        carte,
        curseurX,
        curseurY,
        porteePreview,
        80,
        255,
        120,
        40
    );
}

void GameRenderer::dessinerApercuDrag(
    Rendu& rendu,
    Carte& carte,
    TextureManager& textureManager,
    const std::vector<std::unique_ptr<Tour>>& tours,
    int sourisX,
    int sourisY,
    TypeTour dragTourType
)
{
    if (sourisX < 0 || sourisX >= GameConfig::LARGEUR_MAP ||
        sourisY < 0 || sourisY >= GameConfig::HAUTEUR_FENETRE)
    {
        return;
    }

    int tailleCase = carte.getTailleCase();
    int gridX = sourisX / tailleCase;
    int gridY = sourisY / tailleCase;

    bool libre =
        carte.estConstructible(gridX, gridY) &&
        trouverIndexTour(tours, gridX, gridY) == -1;

    for (const PaletteDef& def : PALETTE_DEFS)
    {
        if (def.type != dragTourType)
        {
            continue;
        }

        SDL_Texture* texture = textureManager.get(def.textureId);
        if (!texture)
        {
            return;
        }

        int dstX = gridX * tailleCase;
        int dstY = gridY * tailleCase;

        rendu.renderCopy(
            texture,
            0,
            def.spriteRow * SPRITE_SIZE,
            SPRITE_SIZE,
            SPRITE_SIZE,
            dstX,
            dstY,
            tailleCase,
            tailleCase
        );

        if (libre)
        {
            rendu.setColor(0, 255, 0, 180);
        }
        else
        {
            rendu.setColor(255, 0, 0, 180);
        }

        rendu.drawRect(dstX, dstY, tailleCase, tailleCase);
        break;
    }
}

void GameRenderer::dessinerCerclePortee(
    Rendu& rendu,
    Carte& carte,
    int gridX,
    int gridY,
    float portee,
    int r,
    int g,
    int b,
    int a
) const
{
    rendu.enableBlend();

    int tailleCase = carte.getTailleCase();

    int centreX = gridX * tailleCase + tailleCase / 2;
    int centreY = gridY * tailleCase + tailleCase / 2;
    int rayon = static_cast<int>(portee);

    rendu.setColor(r, g, b, a);

    for (int y = -rayon; y <= rayon; y++)
    {
        int xMax = static_cast<int>(
            std::sqrt(static_cast<float>(rayon * rayon - y * y))
        );

        rendu.drawLine(
            centreX - xMax,
            centreY + y,
            centreX + xMax,
            centreY + y
        );
    }

    rendu.setColor(r, g, b, 180);

    constexpr float PI = 3.14159265f;

    for (int angle = 0; angle < 360; angle++)
    {
        float rad = angle * PI / 180.0f;

        int x = centreX + static_cast<int>(std::cos(rad) * rayon);
        int y = centreY + static_cast<int>(std::sin(rad) * rayon);

        rendu.drawPoint(x, y);
    }
}

int GameRenderer::trouverIndexTour(
    const std::vector<std::unique_ptr<Tour>>& tours,
    int gridX,
    int gridY
) const
{
    for (int i = 0; i < static_cast<int>(tours.size()); i++)
    {
        if (tours[i]->getGridX() == gridX &&
            tours[i]->getGridY() == gridY)
        {
            return i;
        }
    }

    return -1;
}
