#include "boutton.hpp"

// Le constructeur
Boutton::Boutton(int x, int y, int w, int h, SDL_Color col) 
    : couleur(col) {
    rect = {x, y, w, h};
}

void Boutton::dessiner(SDL_Renderer* renderer) {
    // Remplissage du bouton
    SDL_SetRenderDrawColor(renderer, couleur.r, couleur.g, couleur.b, couleur.a);
    SDL_RenderFillRect(renderer, &rect);

    // Contour noir (pour qu'il soit visible sur la neige)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
}

// La détection du clic
bool Boutton::estClique(int mouseX, int mouseY) {
    SDL_Point p = {mouseX, mouseY};
    return SDL_PointInRect(&p, &rect);
}