#pragma once

#include <SDL2/SDL.h>
#include <memory>


class Rendu {
public:
    Rendu(SDL_Window* window);
    
    ~Rendu() = default;

    Rendu(const Rendu&) = delete;
    Rendu& operator=(const Rendu&) = delete;
    //  A utiliser quand on sera mort ou en changement de scene
    void clear();   
    void present();  

    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

    // pour pouvoir utiliser la fonction malgre les restrictions C++
    SDL_Renderer* getNativeRenderer() const { return m_renderer.get(); }

private:
    // Facon intellegente de détruire rendu a la fin du main
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
};