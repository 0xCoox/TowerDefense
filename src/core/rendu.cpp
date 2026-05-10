#include "rendu.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

Rendu::Rendu(SDL_Window* window)
    : renderer_(nullptr, &SDL_DestroyRenderer)
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

    renderer_.reset(rawRenderer);

    std::cout << "Rendu cree avec succes !" << std::endl;
}

Rendu::~Rendu()
{
    renderer_.reset();
    TTF_Quit();
}

void Rendu::clear()
{
    SDL_RenderClear(renderer_.get());
}

void Rendu::present()
{
    SDL_RenderPresent(renderer_.get());
}

void Rendu::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(renderer_.get(), r, g, b, a);
}

void Rendu::setColor(const SDL_Color& couleur)
{
    SDL_SetRenderDrawColor(
        renderer_.get(),
        couleur.r,
        couleur.g,
        couleur.b,
        couleur.a
    );
}

void Rendu::setBlendMode(SDL_BlendMode mode)
{
    SDL_SetRenderDrawBlendMode(renderer_.get(), mode);
}

void Rendu::enableBlend()
{
    SDL_SetRenderDrawBlendMode(renderer_.get(), SDL_BLENDMODE_BLEND);
}

void Rendu::drawRect(const SDL_Rect& rect)
{
    SDL_RenderDrawRect(renderer_.get(), &rect);
}

void Rendu::drawRect(int x, int y, int w, int h)
{
    SDL_Rect rect = {x, y, w, h};

    SDL_RenderDrawRect(
        renderer_.get(),
        &rect
    );
}

void Rendu::fillRect(const SDL_Rect& rect)
{
    SDL_RenderFillRect(renderer_.get(), &rect);
}

void Rendu::fillRect(int x, int y, int w, int h)
{
    SDL_Rect rect = {x, y, w, h};

    SDL_RenderFillRect(
        renderer_.get(),
        &rect
    );
}

void Rendu::drawLine(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(
        renderer_.get(),
        x1,
        y1,
        x2,
        y2
    );
}

void Rendu::drawPoint(int x, int y)
{
    SDL_RenderDrawPoint(
        renderer_.get(),
        x,
        y
    );
}

void Rendu::renderCopy(
    SDL_Texture* texture,
    const SDL_Rect* src,
    const SDL_Rect* dst
)
{
    SDL_RenderCopy(
        renderer_.get(),
        texture,
        src,
        dst
    );
}

void Rendu::renderCopy(
    SDL_Texture* texture,
    int dstX,
    int dstY,
    int dstW,
    int dstH
)
{
    SDL_Rect dst = {
        dstX,
        dstY,
        dstW,
        dstH
    };

    SDL_RenderCopy(
        renderer_.get(),
        texture,
        nullptr,
        &dst
    );
}

void Rendu::renderCopy(
    SDL_Texture* texture,
    int srcX,
    int srcY,
    int srcW,
    int srcH,
    int dstX,
    int dstY,
    int dstW,
    int dstH
)
{
    SDL_Rect src = {
        srcX,
        srcY,
        srcW,
        srcH
    };

    SDL_Rect dst = {
        dstX,
        dstY,
        dstW,
        dstH
    };

    SDL_RenderCopy(
        renderer_.get(),
        texture,
        &src,
        &dst
    );
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
    SDL_RenderCopyEx(
        renderer_.get(),
        texture,
        src,
        dst,
        angle,
        center,
        flip
    );
}

void Rendu::renderCopyEx(
    SDL_Texture* texture,
    int srcX,
    int srcY,
    int srcW,
    int srcH,
    int dstX,
    int dstY,
    int dstW,
    int dstH,
    double angle,
    int centerX,
    int centerY
)
{
    renderCopyEx(
        texture,
        srcX,
        srcY,
        srcW,
        srcH,
        dstX,
        dstY,
        dstW,
        dstH,
        angle,
        centerX,
        centerY,
        SDL_FLIP_NONE
    );
}

void Rendu::renderCopyEx(
    SDL_Texture* texture,
    int srcX,
    int srcY,
    int srcW,
    int srcH,
    int dstX,
    int dstY,
    int dstW,
    int dstH,
    double angle,
    int centerX,
    int centerY,
    SDL_RendererFlip flip
)
{
    SDL_Rect src = {
        srcX,
        srcY,
        srcW,
        srcH
    };

    SDL_Rect dst = {
        dstX,
        dstY,
        dstW,
        dstH
    };

    SDL_Point center = {
        centerX,
        centerY
    };

    SDL_RenderCopyEx(
        renderer_.get(),
        texture,
        &src,
        &dst,
        angle,
        &center,
        flip
    );
}

void Rendu::renderCopyExWholeTexture(
    SDL_Texture* texture,
    int dstX,
    int dstY,
    int dstW,
    int dstH,
    double angle,
    int centerX,
    int centerY
)
{
    SDL_Rect dst = {
        dstX,
        dstY,
        dstW,
        dstH
    };

    SDL_Point center = {
        centerX,
        centerY
    };

    SDL_RenderCopyEx(
        renderer_.get(),
        texture,
        nullptr,
        &dst,
        angle,
        &center,
        SDL_FLIP_NONE
    );
}

SDL_Texture* Rendu::createTextureFromSurface(SDL_Surface* surface)
{
    return SDL_CreateTextureFromSurface(
        renderer_.get(),
        surface
    );
}

void Rendu::destroyTexture(SDL_Texture* texture)
{
    SDL_DestroyTexture(texture);
}

SDL_Renderer* Rendu::getNativeRenderer() const
{
    return renderer_.get();
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

    int largeur = surface->w;
    int hauteur = surface->h;

    SDL_FreeSurface(surface);

    renderCopy(
        texture,
        x,
        y,
        largeur,
        hauteur
    );

    destroyTexture(texture);
}