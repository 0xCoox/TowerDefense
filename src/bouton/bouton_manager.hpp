#ifndef BOUTTON_MANAGER_HPP
#define BOUTTON_MANAGER_HPP

#include <vector>
#include <memory>
#include "boutton.hpp"

class BouttonManager {
private:
    std::vector<std::unique_ptr<Boutton>> listeBouttons;

public:
    void ajouterBoutton(std::unique_ptr<Boutton> b) {
        listeBouttons.push_back(std::move(b));
    }

    void handleEvents(SDL_Event& event) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            
            for (auto& b : listeBouttons) {
                if (b->estClique(x, y)) {
                    b->action();
                }
            }
        }
    }

    void render(SDL_Renderer* renderer) {
        for (auto& b : listeBouttons) {
            b->dessiner(renderer);
        }
    }
};

#endif