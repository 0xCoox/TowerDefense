#include "rendu.hpp"
#include <stdexcept>
#include <iostream>

Rendu::Rendu(SDL_Window* window)
    : m_renderer(nullptr, &SDL_DestroyRenderer) 
{
    // On crée le renderer matériel avec VSYNC
    SDL_Renderer* rawRenderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!rawRenderer) {
        throw std::runtime_error("Erreur SDL_CreateRenderer : " + std::string(SDL_GetError()));
    }

    // On donne la propriété du pointeur brut à notre smart pointer
    m_renderer.reset(rawRenderer);
    
    std::cout << "Rendu cree avec succes !" << std::endl;
}

void Rendu::clear() {
    SDL_RenderClear(m_renderer.get());
}

void Rendu::present() {
    SDL_RenderPresent(m_renderer.get());
}

void Rendu::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(m_renderer.get(), r, g, b, a);
}