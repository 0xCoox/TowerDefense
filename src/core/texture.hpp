#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include <iostream>

class TextureManager {
public:
    void charger(const std::string& id, const std::string& chemin, SDL_Renderer* renderer) {
        SDL_Texture* tex = IMG_LoadTexture(renderer, chemin.c_str());
        if (!tex) {
            std::cerr << "Erreur chargement : " << chemin << " -> " << IMG_GetError() << std::endl;
            return;
        }
        textures_[id] = tex;
    }

    SDL_Texture* get(const std::string& id) const {
        auto it = textures_.find(id);
        if (it != textures_.end()) {
            return it->second;
        }
        return nullptr;
    }

    SDL_Rect calculerSpriteRect(int colonne, int ligne, int tailleSprite) {
    SDL_Rect rect;
    rect.x = colonne * tailleSprite; 
    rect.y = ligne * tailleSprite;   
    rect.w = tailleSprite;
    rect.h = tailleSprite;
    return rect;
    }

    void nettoyer() {
        for (auto const& [id, tex] : textures_) {
            SDL_DestroyTexture(tex);
        }
        textures_.clear();
    }

private:
    std::map<std::string, SDL_Texture*> textures_;
};