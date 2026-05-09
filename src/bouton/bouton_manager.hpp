#ifndef BOUTTON_MANAGER_HPP
#define BOUTTON_MANAGER_HPP

#include "boutton.hpp"

#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <memory>
#include <vector>

class BouttonManager
{
private:
    std::vector<std::unique_ptr<Boutton>> listeBouttons_;
    TTF_Font* font_;

public:
    BouttonManager()
        : font_(nullptr)
    {
        if (TTF_WasInit() == 0)
        {
            if (TTF_Init() == -1)
            {
                std::cout << "Erreur TTF_Init : "
                          << TTF_GetError()
                          << std::endl;
                return;
            }
        }

        font_ = TTF_OpenFont(
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
            18
        );

        if (font_ == nullptr)
        {
            std::cout << "Erreur chargement police bouton : "
                      << TTF_GetError()
                      << std::endl;
        }
    }

    ~BouttonManager()
    {
        if (font_ != nullptr)
        {
            TTF_CloseFont(font_);
            font_ = nullptr;
        }

        // Ne pas faire TTF_Quit ici.
        // Le HUD utilise aussi SDL_ttf.
    }

    void ajouterBoutton(std::unique_ptr<Boutton> bouton)
    {
        listeBouttons_.push_back(std::move(bouton));
    }

    void handleClick(int mouseX, int mouseY)
    {
        for (auto& bouton : listeBouttons_)
        {
            if (bouton->estClique(mouseX, mouseY))
            {
                bouton->action();
                return;
            }
        }
    }

    void render(SDL_Renderer* renderer)
    {
        for (const auto& bouton : listeBouttons_)
        {
            bouton->dessiner(renderer, font_);
        }
    }
};

#endif