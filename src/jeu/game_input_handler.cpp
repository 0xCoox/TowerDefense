#include "game_input_handler.hpp"

#include <array>
#include <iostream>

namespace
{
    struct ToucheTour
    {
        InputManager::Key touche;
        TypeTour typeTour;
    };

    constexpr std::array<ToucheTour, 5> TOUCHES_TOURS = {
        ToucheTour{InputManager::Key::Num1, TypeTour::Basique},
        ToucheTour{InputManager::Key::Num2, TypeTour::Sniper},
        ToucheTour{InputManager::Key::Num3, TypeTour::Canon},
        ToucheTour{InputManager::Key::Num4, TypeTour::Glace},
        ToucheTour{InputManager::Key::Num5, TypeTour::AntiAir}
    };
}

void GameInputHandler::traiterEntrees(
    InputManager& input,
    BouttonManager& guiManager,
    bool& estLance,
    bool& estPause,
    int& curseurX,
    int& curseurY,
    const std::function<void(TypeTour)>& selectionnerTour,
    const std::function<void()>& essayerAjouterTour,
    const std::function<void()>& lancerVague
) const
{
    input.update();

    if (input.isMouseButtonPressed(InputManager::MouseButton::Left))
    {
        guiManager.handleClick(
            input.getMouseX(),
            input.getMouseY()
        );
    }

    if (input.shouldQuit() || input.isKeyPressed(InputManager::Key::Escape))
    {
        estLance = false;
    }

    if (input.isKeyPressed(InputManager::Key::Space))
    {
        estPause = !estPause;

        if (estPause)
        {
            std::cout << "Pause" << std::endl;
        }
        else
        {
            std::cout << "Reprise" << std::endl;
        }
    }

    if (input.isKeyPressed(InputManager::Key::Return))
    {
        lancerVague();
    }

    if (input.isKeyPressed(InputManager::Key::Up))
    {
        curseurY--;
    }

    if (input.isKeyPressed(InputManager::Key::Down))
    {
        curseurY++;
    }

    if (input.isKeyPressed(InputManager::Key::Left))
    {
        curseurX--;
    }

    if (input.isKeyPressed(InputManager::Key::Right))
    {
        curseurX++;
    }

    for (const ToucheTour& toucheTour : TOUCHES_TOURS)
    {
        if (input.isKeyPressed(toucheTour.touche))
        {
            selectionnerTour(toucheTour.typeTour);
            break;
        }
    }

    if (input.isKeyPressed(InputManager::Key::A))
    {
        essayerAjouterTour();
    }
}