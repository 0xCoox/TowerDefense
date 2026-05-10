#include "game_input_handler.hpp"

#include <SDL2/SDL.h>

#include <array>
#include <iostream>

namespace
{
    struct ToucheTour
    {
        SDL_Keycode touche;
        TypeTour typeTour;
    };

    constexpr std::array<ToucheTour, 5> TOUCHES_TOURS = {
        ToucheTour{SDLK_1, TypeTour::Basique},
        ToucheTour{SDLK_2, TypeTour::Sniper},
        ToucheTour{SDLK_3, TypeTour::Canon},
        ToucheTour{SDLK_4, TypeTour::Glace},
        ToucheTour{SDLK_5, TypeTour::AntiAir}
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

    if (input.isMouseButtonPressed(SDL_BUTTON_LEFT))
    {
        guiManager.handleClick(
            input.getMouseX(),
            input.getMouseY()
        );
    }

    if (input.shouldQuit() || input.isKeyPressed(SDLK_ESCAPE))
    {
        estLance = false;
    }

    if (input.isKeyPressed(SDLK_SPACE))
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

    if (input.isKeyPressed(SDLK_RETURN))
    {
        lancerVague();
    }

    if (input.isKeyPressed(SDLK_UP))
    {
        curseurY--;
    }

    if (input.isKeyPressed(SDLK_DOWN))
    {
        curseurY++;
    }

    if (input.isKeyPressed(SDLK_LEFT))
    {
        curseurX--;
    }

    if (input.isKeyPressed(SDLK_RIGHT))
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

    if (input.isKeyPressed(SDLK_a))
    {
        essayerAjouterTour();
    }
}