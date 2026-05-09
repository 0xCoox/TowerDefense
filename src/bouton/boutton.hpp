#ifndef BOUTTON_HPP
#define BOUTTON_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <functional>
#include <string>

class Boutton
{
private:
    SDL_Rect rect_;
    SDL_Color couleur_;
    SDL_Color couleurTexte_;
    std::string texte_;
    std::function<void()> action_;

public:
    Boutton(
        int x,
        int y,
        int w,
        int h,
        const std::string& texte,
        SDL_Color couleur,
        std::function<void()> action
    );

    void action();
    void dessiner(SDL_Renderer* renderer, TTF_Font* font) const;
    bool estClique(int mouseX, int mouseY) const;
};

#endif