#include "input_manager.hpp"

void InputManager::update()
{
    m_pressedKeys.clear();
    m_pressedMouseButtons.clear();

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            m_shouldQuit = true;
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.repeat == 0)
            {
                m_pressedKeys.insert(event.key.keysym.sym);
            }
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            m_pressedMouseButtons.insert(event.button.button);
        }
    }

    m_keyboardState = SDL_GetKeyboardState(nullptr);
    m_mouseButtons = SDL_GetMouseState(&m_mouseX, &m_mouseY);
}

bool InputManager::shouldQuit() const
{
    return m_shouldQuit;
}

bool InputManager::isKeyDown(SDL_Keycode key) const
{
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key);

    if (m_keyboardState == nullptr)
    {
        return false;
    }

    return m_keyboardState[scancode];
}

bool InputManager::isKeyPressed(SDL_Keycode key) const
{
    return m_pressedKeys.find(key) != m_pressedKeys.end();
}

bool InputManager::isMouseButtonDown(Uint8 button) const
{
    return (m_mouseButtons & SDL_BUTTON(button)) != 0;
}

bool InputManager::isMouseButtonPressed(Uint8 button) const
{
    return m_pressedMouseButtons.find(button) != m_pressedMouseButtons.end();
}

int InputManager::getMouseX() const
{
    return m_mouseX;
}

int InputManager::getMouseY() const
{
    return m_mouseY;
}   