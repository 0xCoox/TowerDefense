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
    pressedKeys_.clear();
    pressedMouseButtons_.clear();

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            shouldQuit_ = true;
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.repeat == 0)
            {
                pressedKeys_.insert(event.key.keysym.sym);
            }
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            pressedMouseButtons_.insert(event.button.button);
        }
    }

    keyboardState_ = SDL_GetKeyboardState(nullptr);
    mouseButtons_ = SDL_GetMouseState(&mouseX_, &mouseY_);
}

bool InputManager::shouldQuit() const
{
    return shouldQuit_;
}

bool InputManager::isKeyDown(SDL_Keycode key) const
{
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key);

    if (keyboardState_ == nullptr)
    {
        return false;
    }

    return keyboardState_[scancode];
}

bool InputManager::isKeyPressed(SDL_Keycode key) const
{
    return pressedKeys_.find(key) != pressedKeys_.end();
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
    return (mouseButtons_ & SDL_BUTTON(button)) != 0;
}

bool InputManager::isMouseButtonPressed(Uint8 button) const
{
    return pressedMouseButtons_.find(button) != pressedMouseButtons_.end();
}

bool InputManager::isMouseButtonDown(MouseButton button) const
{
    return isMouseButtonDown(toSDLButton(button));
}

bool InputManager::isMouseButtonPressed(MouseButton button) const
{
    return isMouseButtonPressed(toSDLButton(button));
}
