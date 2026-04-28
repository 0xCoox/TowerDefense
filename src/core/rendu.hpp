#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>
#include <string>

class Rendu
{
private:
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;

public:
    explicit Rendu(SDL_Window* window);
    ~Rendu();

    Rendu(const Rendu&) = delete;
    Rendu& operator=(const Rendu&) = delete;

    void clear();
    void present();

    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    SDL_Renderer* getNativeRenderer() const;

    void dessinerTexte(
        TTF_Font* font,
        const std::string& texte,
        int x,
        int y,
        SDL_Color couleur
    );
};