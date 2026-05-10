#pragma once

#include "game_input_handler.hpp"
#include "game_world.hpp"
#include "hud.hpp"

#include "../bouton/bouton_manager.hpp"
#include "../core/input_manager.hpp"
#include "../core/texture.hpp"
#include "../tours/type_tour.hpp"

class GameInteractionHandler
{
private:
    GameInputHandler inputHandler_;

    int curseurX_;
    int curseurY_;

    TypeTour typeTourSelectionne_;

    bool afficherPorteePlacement_;

    int tourSelectionneeIndex_;
    bool selectionVerrouillee_;

    bool dragTourActif_;
    TypeTour dragTourType_;
    int dragTourCout_;

    bool sourisGaucheAvant_;

public:
    GameInteractionHandler(
        TypeTour typeTourParDefaut,
        int curseurXInitial,
        int curseurYInitial
    );

    void traiterEntrees(
        InputManager& input,
        BouttonManager& guiManager,
        Hud& hud,
        GameWorld& world,
        TextureManager& textureManager,
        bool& estLance,
        bool& estPause
    );

    void ameliorerTourSelectionnee(GameWorld& world);
    void vendreTourSelectionnee(GameWorld& world);

    int getCurseurX() const { return curseurX_; }
    int getCurseurY() const { return curseurY_; }

    TypeTour getTypeTourSelectionne() const
    {
        return typeTourSelectionne_;
    }

    bool estDragTourActif() const
    {
        return dragTourActif_;
    }

    TypeTour getDragTourType() const
    {
        return dragTourType_;
    }

    bool doitAfficherPorteePlacement() const
    {
        return afficherPorteePlacement_;
    }

private:
    void selectionnerTour(TypeTour typeTour);

    void essayerAjouterTour(
        GameWorld& world,
        TextureManager& textureManager
    );

    void gererClicSouris(
        Hud& hud,
        GameWorld& world,
        TextureManager& textureManager,
        int sourisX,
        int sourisY
    );

    void terminerDragTour(
        GameWorld& world,
        TextureManager& textureManager,
        int sourisX,
        int sourisY
    );

    bool sourisDansMap(int sourisX, int sourisY) const;

    int getGridXDepuisSouris(
        const GameWorld& world,
        int sourisX
    ) const;

    int getGridYDepuisSouris(
        const GameWorld& world,
        int sourisY
    ) const;

    void getCoordonneesTourSelectionnee(
        const GameWorld& world,
        int& gridX,
        int& gridY
    ) const;
};