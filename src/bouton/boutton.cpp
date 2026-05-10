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
    : x_(x),
      y_(y),
      largeur_(w),
      hauteur_(h),
      couleur_(couleur),
      couleurTexte_{255, 255, 255, 255},
      texte_(texte),
      action_(action)
{
}

void Boutton::action()
{
    if (action_)
    {
        action_();
    }
}

void Boutton::dessiner(
    Rendu& rendu,
    TTF_Font* font
) const
{
    rendu.enableBlend();

    // Fond du bouton
    rendu.setColor(couleur_);

    rendu.fillRect(
        x_,
        y_,
        largeur_,
        hauteur_
    );

    // Bordure noire
    rendu.setColor(0, 0, 0, 255);

    rendu.drawRect(
        x_,
        y_,
        largeur_,
        hauteur_
    );

    // Si la police n'est pas chargée, on dessine seulement le rectangle
    if (font == nullptr)
    {
        return;
    }

    int texteLargeur = 0;
    int texteHauteur = 0;

    if (TTF_SizeUTF8(
            font,
            texte_.c_str(),
            &texteLargeur,
            &texteHauteur
        ) != 0)
    {
        return;
    }

    int texteX = x_ + (largeur_ - texteLargeur) / 2;
    int texteY = y_ + (hauteur_ - texteHauteur) / 2;

    rendu.dessinerTexte(
        font,
        texte_,
        texteX,
        texteY,
        couleurTexte_
    );
}

bool Boutton::estClique(
    int mouseX,
    int mouseY
) const
{
    return mouseX >= x_ &&
           mouseX <= x_ + largeur_ &&
           mouseY >= y_ &&
           mouseY <= y_ + hauteur_;
}