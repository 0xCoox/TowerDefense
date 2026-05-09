#include "window.hpp"
#include <iostream>
#include <stdexcept>

Window::Window(const std::string& title, int width, int height) 
    : m_window(nullptr, &SDL_DestroyWindow) // On initialise le pointeur avec le destructeur
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Erreur SDL_Init : " + std::string(SDL_GetError()));
    }

    // Creation fenetre
    SDL_Window* rawWindow = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!rawWindow) {
        SDL_Quit(); 
        throw std::runtime_error("Erreur SDL_CreateWindow : " + std::string(SDL_GetError()));
    }

    m_window.reset(rawWindow);
    
    std::cout << "Fenetre creee avec succes !" << std::endl;
}