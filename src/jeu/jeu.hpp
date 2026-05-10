#pragma once

#include "game_interaction_handler.hpp"
#include "game_renderer.hpp"
#include "game_world.hpp"
#include "hud.hpp"

#include "../bouton/bouton_manager.hpp"
#include "../core/input_manager.hpp"
#include "../core/rendu.hpp"
#include "../core/texture.hpp"
#include "../core/window.hpp"
#include "../tours/type_tour.hpp"

#include <chrono>

class Jeu
{
private:
    Window window_;
    Rendu rendu_;

    InputManager input_;

    Hud hud_;

    bool estLance_;
    bool estPause_;

    GameWorld world_;

    TextureManager textureManager_;
    BouttonManager guiManager_;

    GameRenderer gameRenderer_;
    GameInteractionHandler interactionHandler_;

    std::chrono::steady_clock::time_point dernierTemps_;

public:
    Jeu();

    void lancer();

private:
    void traiterEntrees();
    void mettreAJour(float dt);
    void dessiner();

    void afficherCommandes() const;
};