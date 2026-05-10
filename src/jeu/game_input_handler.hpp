#pragma once

#include "../core/input_manager.hpp"
#include "../bouton/bouton_manager.hpp"
#include "../tours/type_tour.hpp"

#include <functional>

class GameInputHandler
{
public:
    GameInputHandler() = default;
    ~GameInputHandler() = default;

    void traiterEntrees(
        InputManager& input,
        BouttonManager& guiManager,
        bool& estLance,
        bool& estPause,
        int& curseurX,
        int& curseurY,
        const std::function<void(TypeTour)>& selectionnerTour,
        const std::function<void()>& essayerAjouterTour,
        const std::function<void()>& lancerVague
    ) const;
};