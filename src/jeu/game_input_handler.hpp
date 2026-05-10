#pragma once

#include "../core/input_manager.hpp"
#include "../bouton/bouton_manager.hpp"
#include "../tours/type_tour.hpp"

#include <functional>
/**
 * @brief Gère les entrées simples du joueur.
 *
 * Cette classe lit l'état de InputManager et transforme les touches clavier
 * ou les clics souris en actions simples : déplacement du curseur, pause,
 * sélection d'une tour, placement ou lancement de vague.
 *
 * Elle ne possède pas le monde du jeu. Les actions importantes sont données
 * sous forme de callbacks.
 */
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