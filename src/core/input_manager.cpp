#include "input_manager.hpp"

SDL_Keycode InputManager::toSDLKey(Key key)
{
    switch (key)
    {
        case Key::Escape:
            return SDLK_ESCAPE;
        case Key::Space:
            return SDLK_SPACE;
        case Key::Return:
            return SDLK_RETURN;
        case Key::Up:
            return SDLK_UP;
        case Key::Down:
            return SDLK_DOWN;
        case Key::Left:
            return SDLK_LEFT;
        case Key::Right:
            return SDLK_RIGHT;
        case Key::A:
            return SDLK_a;
        case Key::Num1:
            return SDLK_1;
        case Key::Num2:
            return SDLK_2;
        case Key::Num3:
            return SDLK_3;
        case Key::Num4:
            return SDLK_4;
        case Key::Num5:
            return SDLK_5;
    }

    return SDLK_UNKNOWN;
}

Uint8 InputManager::toSDLButton(MouseButton button)
{
    switch (button)
    {
        case MouseButton::Left:
            return SDL_BUTTON_LEFT;
        case MouseButton::Middle:
            return SDL_BUTTON_MIDDLE;
        case MouseButton::Right:
            return SDL_BUTTON_RIGHT;
    }

    return 0;
}

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

bool InputManager::isKeyDown(Key key) const
{
    return isKeyDown(toSDLKey(key));
}

bool InputManager::isKeyPressed(Key key) const
{
    return isKeyPressed(toSDLKey(key));
}

bool InputManager::isMouseButtonDown(Uint8 button) const
{
    return (m_mouseButtons & SDL_BUTTON(button)) != 0;
}

bool InputManager::isMouseButtonPressed(Uint8 button) const
{
    return m_pressedMouseButtons.find(button) != m_pressedMouseButtons.end();
}

bool InputManager::isMouseButtonDown(MouseButton button) const
{
    return isMouseButtonDown(toSDLButton(button));
}

bool InputManager::isMouseButtonPressed(MouseButton button) const
{
    return isMouseButtonPressed(toSDLButton(button));
}

int InputManager::getMouseX() const
{
    return m_mouseX;
}

int InputManager::getMouseY() const
{
    return m_mouseY;
}   