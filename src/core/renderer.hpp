#pragma once

#include <SDL2/SDL.h>
#include <memory>

class Renderer {
public:
    // Le constructeur prend le pointeur brut de la fenêtre pour s'y attacher
    Renderer(SDL_Window* window);
    
    ~Renderer() = default;

    // Pas de copie !
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    // Les fonctions de base pour dessiner
    void clear();    // Efface l'écran (met tout en noir par exemple)
    void present();  // Affiche ce qu'on vient de dessiner

    // Accesseur pour le reste du jeu
    SDL_Renderer* getNativeRenderer() const { return m_renderer.get(); }

private:
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
};