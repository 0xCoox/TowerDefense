#include "window.hpp"
#include <iostream>
#include <stdexcept>

Window::Window(const std::string& title, int width, int height) 
    : m_window(nullptr, &SDL_DestroyWindow) // On initialise le pointeur avec le destructeur
{
    // 1. Initialiser le sous-système Vidéo de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Erreur SDL_Init : " + std::string(SDL_GetError()));
    }

    // 2. Créer la fenêtre
    SDL_Window* rawWindow = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    // 3. Vérifier si la création a réussi
    if (!rawWindow) {
        SDL_Quit(); // On nettoie avant de partir
        throw std::runtime_error("Erreur SDL_CreateWindow : " + std::string(SDL_GetError()));
    }

    // 4. On transfère la possession du pointeur brut au smart pointer
    m_window.reset(rawWindow);
    
    std::cout << "Fenetre creee avec succes !" << std::endl;
}