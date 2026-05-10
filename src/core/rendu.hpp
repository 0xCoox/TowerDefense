#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>
#include <string>

/**
 * @brief Encapsule le rendu SDL2 du jeu.
 *
 * Cette classe centralise les appels à SDL_Renderer afin que les autres classes
 * du projet n'aient pas à manipuler directement SDL_Rect, SDL_RenderCopy,
 * SDL_RenderCopyEx ou SDL_RenderDrawLine.
 *
 * Elle est responsable de :
 * - effacer et présenter l'écran ;
 * - dessiner des rectangles, lignes et points ;
 * - afficher des textures ;
 * - afficher du texte avec SDL_ttf.
 */

class Rendu
{
private:
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_;

public:
    explicit Rendu(SDL_Window* window);
    ~Rendu();

    void clear();
    void present();

    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void setColor(const SDL_Color& couleur);

    void setBlendMode(SDL_BlendMode mode);
    void enableBlend();

    void drawRect(const SDL_Rect& rect);
    void drawRect(int x, int y, int w, int h);

    void fillRect(const SDL_Rect& rect);
    void fillRect(int x, int y, int w, int h);

    void drawLine(int x1, int y1, int x2, int y2);
    void drawPoint(int x, int y);

    void renderCopy(
        SDL_Texture* texture,
        const SDL_Rect* src,
        const SDL_Rect* dst
    );

    void renderCopy(
        SDL_Texture* texture,
        int dstX,
        int dstY,
        int dstW,
        int dstH
    );

    void renderCopy(
        SDL_Texture* texture,
        int srcX,
        int srcY,
        int srcW,
        int srcH,
        int dstX,
        int dstY,
        int dstW,
        int dstH
    );

    void renderCopyEx(
        SDL_Texture* texture,
        const SDL_Rect* src,
        const SDL_Rect* dst,
        double angle,
        const SDL_Point* center,
        SDL_RendererFlip flip
    );

    void renderCopyEx(
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
    );

    void renderCopyEx(
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
    );

    void renderCopyExWholeTexture(
        SDL_Texture* texture,
        int dstX,
        int dstY,
        int dstW,
        int dstH,
        double angle,
        int centerX,
        int centerY
    );

    SDL_Texture* createTextureFromSurface(SDL_Surface* surface);
    void destroyTexture(SDL_Texture* texture);

    SDL_Renderer* getNativeRenderer() const;
    /**
     * @brief Dessine un texte à l'écran.
     *
     * Cette fonction crée temporairement une surface puis une texture SDL à partir
     * du texte donné, l'affiche, puis libère la texture créée.
     *
     * @param font Police utilisée pour le texte.
     * @param texte Texte à afficher.
     * @param x Position X en pixels.
     * @param y Position Y en pixels.
     * @param couleur Couleur du texte.
     */
    void dessinerTexte(
        TTF_Font* font,
        const std::string& texte,
        int x,
        int y,
        SDL_Color couleur
    );
};