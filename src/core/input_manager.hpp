#pragma once

#include <SDL2/SDL.h>
#include <unordered_set>

class InputManager
{
public:
    enum class Key
    {
        Escape,
        Space,
        Return,
        Up,
        Down,
        Left,
        Right,
        A,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5
    };

    enum class MouseButton
    {
        Left,
        Middle,
        Right
    };

    InputManager() = default;

    void update();

    bool shouldQuit() const;

    bool isKeyDown(SDL_Keycode key) const;
    bool isKeyPressed(SDL_Keycode key) const;

    bool isKeyDown(Key key) const;
    bool isKeyPressed(Key key) const;

    bool isMouseButtonDown(Uint8 button) const;
    bool isMouseButtonPressed(Uint8 button) const;

    bool isMouseButtonDown(MouseButton button) const;
    bool isMouseButtonPressed(MouseButton button) const;

    int getMouseX() const { return mouseX_; }
    int getMouseY() const { return mouseY_; }

private:
    static SDL_Keycode toSDLKey(Key key);
    static Uint8 toSDLButton(MouseButton button);

    bool shouldQuit_ = false;

    const Uint8* keyboardState_ = nullptr;
    std::unordered_set<SDL_Keycode> pressedKeys_;

    int mouseX_ = 0;
    int mouseY_ = 0;
    Uint32 mouseButtons_ = 0;

    std::unordered_set<Uint8> pressedMouseButtons_;
};