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
    void setColor(const SDL_Color& couleur);
    void setBlendMode(SDL_BlendMode mode);

    void drawRect(const SDL_Rect& rect);
    void fillRect(const SDL_Rect& rect);
    void drawLine(int x1, int y1, int x2, int y2);
    void drawPoint(int x, int y);

    void renderCopy(
        SDL_Texture* texture,
        const SDL_Rect* src,
        const SDL_Rect* dst
    );

    void renderCopyEx(
        SDL_Texture* texture,
        const SDL_Rect* src,
        const SDL_Rect* dst,
        double angle,
        const SDL_Point* center,
        SDL_RendererFlip flip
    );

    SDL_Texture* createTextureFromSurface(SDL_Surface* surface);
    void destroyTexture(SDL_Texture* texture);

    SDL_Renderer* getNativeRenderer() const;

    void dessinerTexte(
        TTF_Font* font,
        const std::string& texte,
        int x,
        int y,
        SDL_Color couleur
    );
};