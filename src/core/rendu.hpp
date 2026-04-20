#pragma once

#include <SDL2/SDL.h>
#include <memory>

class Rendu {
public:
    Rendu(SDL_Window* window);
    
    ~Rendu() = default;

    Rendu(const Rendu&) = delete;
    Rendu& operator=(const Rendu&) = delete;

    void clear();   
    void present();  

    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

    SDL_Renderer* getNativeRenderer() const { return m_renderer.get(); }

private:
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
};