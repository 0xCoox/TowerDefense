#include "rendu.hpp"
#include <stdexcept>
#include <iostream>

Rendu::Rendu(SDL_Window* window)
//on init a  null mais on lui accorde deja la func destruct
: m_renderer(nullptr, &SDL_DestroyRenderer) 
{
    // On crée le renderer matériel avec VSYNC
    SDL_Renderer* rawRenderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    // On donne la propriété du pointeur brut à notre smart pointer, creation réussi 
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