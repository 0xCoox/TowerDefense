#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <memory>

class Window {
public:
    // Constructeur : initialise la SDL et crée la fenêtre
    Window(const std::string& title, int width, int height);

    // Destructeur : on utilise = default car le unique_ptr gère tout
    ~Window() = default;

    // INTERDICTION DE COPIER la fenêtre (critère de propreté)
    // On ne veut pas que deux objets Window essaient de gérer la même fenêtre SDL
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // Accesseur pour récupérer le pointeur brut (nécessaire pour le Renderer plus tard)
    SDL_Window* getNativeWindow() const { return m_window.get(); }

private:
    // Le Smart Pointer : il contient la fenêtre ET la fonction pour la détruire
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
};