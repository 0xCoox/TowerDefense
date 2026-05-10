#include "rendu.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

Rendu::Rendu(SDL_Window* window)
    : m_renderer(nullptr, &SDL_DestroyRenderer)
{
    if (TTF_Init() == -1)
    {
        throw std::runtime_error(
            "Erreur TTF_Init : " + std::string(TTF_GetError())
        );
    }

    SDL_Renderer* rawRenderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (rawRenderer == nullptr)
    {
        throw std::runtime_error(
            "Erreur SDL_CreateRenderer : " + std::string(SDL_GetError())
        );
    }

    m_renderer.reset(rawRenderer);

    std::cout << "Rendu cree avec succes !" << std::endl;
}

Rendu::~Rendu()
{
    m_renderer.reset();
    TTF_Quit();
}

void Rendu::clear()
{
    SDL_RenderClear(m_renderer.get());
}

void Rendu::present()
{
    SDL_RenderPresent(m_renderer.get());
}

void Rendu::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(m_renderer.get(), r, g, b, a);
}

void Rendu::setColor(const SDL_Color& couleur)
{
    SDL_SetRenderDrawColor(
        m_renderer.get(),
        couleur.r,
        couleur.g,
        couleur.b,
        couleur.a
    );
}

void Rendu::setBlendMode(SDL_BlendMode mode)
{
    SDL_SetRenderDrawBlendMode(m_renderer.get(), mode);
}

void Rendu::drawRect(const SDL_Rect& rect)
{
    SDL_RenderDrawRect(m_renderer.get(), &rect);
}

void Rendu::fillRect(const SDL_Rect& rect)
{
    SDL_RenderFillRect(m_renderer.get(), &rect);
}

void Rendu::drawLine(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(m_renderer.get(), x1, y1, x2, y2);
}

void Rendu::drawPoint(int x, int y)
{
    SDL_RenderDrawPoint(m_renderer.get(), x, y);
}

void Rendu::renderCopy(
    SDL_Texture* texture,
    const SDL_Rect* src,
    const SDL_Rect* dst
)
{
    SDL_RenderCopy(m_renderer.get(), texture, src, dst);
}

void Rendu::renderCopyEx(
    SDL_Texture* texture,
    const SDL_Rect* src,
    const SDL_Rect* dst,
    double angle,
    const SDL_Point* center,
    SDL_RendererFlip flip
)
{
    SDL_RenderCopyEx(m_renderer.get(), texture, src, dst, angle, center, flip);
}

SDL_Texture* Rendu::createTextureFromSurface(SDL_Surface* surface)
{
    return SDL_CreateTextureFromSurface(m_renderer.get(), surface);
}

void Rendu::destroyTexture(SDL_Texture* texture)
{
    SDL_DestroyTexture(texture);
}

SDL_Renderer* Rendu::getNativeRenderer() const
{
    return m_renderer.get();
}

void Rendu::dessinerTexte(
    TTF_Font* font,
    const std::string& texte,
    int x,
    int y,
    SDL_Color couleur
)
{
    if (font == nullptr)
    {
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Blended(
        font,
        texte.c_str(),
        couleur
    );

    if (surface == nullptr)
    {
        std::cerr << "Erreur TTF_RenderText_Blended : "
                  << TTF_GetError()
                  << std::endl;
        return;
    }

    SDL_Texture* texture = createTextureFromSurface(surface);

    if (texture == nullptr)
    {
        std::cerr << "Erreur SDL_CreateTextureFromSurface : "
                  << SDL_GetError()
                  << std::endl;

        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect destination = {
        x,
        y,
        surface->w,
        surface->h
    };

    SDL_FreeSurface(surface);

    renderCopy(texture, nullptr, &destination);

    destroyTexture(texture);
}