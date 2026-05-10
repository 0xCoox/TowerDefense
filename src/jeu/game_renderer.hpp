#pragma once

#include "../core/rendu.hpp"
#include "../core/joueur.hpp"
#include "../core/texture.hpp"

#include "../carte/carte.hpp"

#include "../entiter/ennemi.hpp"
#include "../entiter/projectile.hpp"

#include "../tours/tour.hpp"

#include "../bouton/bouton_manager.hpp"

#include "hud.hpp"

#include <memory>
#include <vector>

class GameRenderer
{
public:
    GameRenderer() = default;
    ~GameRenderer() = default;

    void dessiner(
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
        int numeroVague,
        int typeTourSelectionne,
        bool estPause,
        bool afficherPorteePlacement
    );

private:
    float getPorteeTourSelectionnee(
        int typeTourSelectionne,
        int curseurX,
        int curseurY,
        TextureManager& textureManager
    );

    void dessinerPorteeAuCurseur(
        Rendu& rendu,
        Carte& carte,
        TextureManager& textureManager,
        const std::vector<std::unique_ptr<Tour>>& tours,
        int curseurX,
        int curseurY,
        int typeTourSelectionne,
        bool afficherPorteePlacement
    );

    void dessinerCerclePortee(
        Rendu& rendu,
        Carte& carte,
        int gridX,
        int gridY,
        float portee,
        int r,
        int g,
        int b,
        int a
    ) const;

    int trouverIndexTour(
        const std::vector<std::unique_ptr<Tour>>& tours,
        int gridX,
        int gridY
    ) const;
};