#pragma once

#include <SDL2/SDL.h>
#include <unordered_set>

class InputManager
{
public:
    InputManager() = default;

    void update();

    bool shouldQuit() const;

    // True si la touche est maintenue enfoncée
    bool isKeyDown(SDL_Keycode key) const;

    // True seulement au moment où la touche vient d'être appuyée
    bool isKeyPressed(SDL_Keycode key) const;

private:
    bool m_shouldQuit = false;

    // Etat actuel du clavier donné par SDL
    const Uint8* m_keyboardState = nullptr;

    // Touches appuyées pendant cette frame uniquement
    std::unordered_set<SDL_Keycode> m_pressedKeys;
};