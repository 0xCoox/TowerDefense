#pragma once

#include <SDL2/SDL.h>
#include <unordered_set>

class InputManager
{
public:
    InputManager() = default;

    void update();

    bool shouldQuit() const;

    bool isKeyDown(SDL_Keycode key) const;
    bool isKeyPressed(SDL_Keycode key) const;

    bool isMouseButtonDown(Uint8 button) const;
    bool isMouseButtonPressed(Uint8 button) const;

    int getMouseX() const;
    int getMouseY() const;

private:
    bool m_shouldQuit = false;

    const Uint8* m_keyboardState = nullptr;
    std::unordered_set<SDL_Keycode> m_pressedKeys;

    int m_mouseX = 0;
    int m_mouseY = 0;
    Uint32 m_mouseButtons = 0;

    std::unordered_set<Uint8> m_pressedMouseButtons;
};