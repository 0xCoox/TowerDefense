#include "boutton.hpp"

Boutton::Boutton(
    int x,
    int y,
    int w,
    int h,
    const std::string& texte,
    SDL_Color couleur,
    std::function<void()> action
)
    : couleur_(couleur),
      couleurTexte_{255, 255, 255, 255},
      texte_(texte),
      action_(action)
{
    rect_ = {x, y, w, h};
}

void Boutton::action()
{
    if (action_)
    {
        action_();
    }
}

void Boutton::dessiner(Rendu& rendu, TTF_Font* font) const
{
    rendu.setBlendMode(SDL_BLENDMODE_BLEND);

    // Fond du bouton
    rendu.setColor(couleur_);
    rendu.fillRect(rect_);

    // Bordure noire
    rendu.setColor(0, 0, 0, 255);
    rendu.drawRect(rect_);

    // Si la police n'est pas chargée, on dessine seulement le rectangle
    if (font == nullptr)
    {
        return;
    }

    SDL_Surface* surfaceTexte = TTF_RenderUTF8_Blended(
        font,
        texte_.c_str(),
        couleurTexte_
    );

    if (surfaceTexte == nullptr)
    {
        return;
    }

    SDL_Texture* textureTexte = rendu.createTextureFromSurface(surfaceTexte);

    if (textureTexte == nullptr)
    {
        SDL_FreeSurface(surfaceTexte);
        return;
    }

    SDL_Rect rectTexte;
    rectTexte.w = surfaceTexte->w;
    rectTexte.h = surfaceTexte->h;
    rectTexte.x = rect_.x + (rect_.w - rectTexte.w) / 2;
    rectTexte.y = rect_.y + (rect_.h - rectTexte.h) / 2;

    rendu.renderCopy(textureTexte, nullptr, &rectTexte);

    rendu.destroyTexture(textureTexte);
    SDL_FreeSurface(surfaceTexte);
}

bool Boutton::estClique(int mouseX, int mouseY) const
{
    SDL_Point point = {mouseX, mouseY};
    return SDL_PointInRect(&point, &rect_);
}