#ifndef BOUTTON_HPP
#define BOUTTON_HPP

#include <SDL2/SDL.h>

class Boutton {
protected:
    SDL_Rect rect;
    SDL_Color couleur;

public:
    Boutton(int x, int y, int w, int h, SDL_Color col);
    virtual ~Boutton() {}

    virtual void action() = 0;

    virtual void dessiner(SDL_Renderer* renderer);

    bool estClique(int mouseX, int mouseY);
};

#endif