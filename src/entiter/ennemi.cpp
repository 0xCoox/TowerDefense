#include "ennemi.hpp"
#include "../core/rendu.hpp" 

Ennemi::Ennemi(float x, float y, float vitesse, int pv)
    : Entite(x, y, TypeEntite::Ennemi), m_vitesse(vitesse), m_pv(pv) 
{
}

void Ennemi::update(float dt) {
    // code pas top, a revoir pour la suite du projet
    m_x += m_vitesse * dt;
}

void Ennemi::render(Rendu& rendu) const {
    // On utilisera sdl pour plus tard :)
    SDL_Rect rect = {
        static_cast<int>(m_x),
        static_cast<int>(m_y),
        30,
        30
    };

    // pareil juste test
    rendu.setColor(255, 0, 0, 255);
    SDL_RenderFillRect(rendu.getNativeRenderer(), &rect);
}