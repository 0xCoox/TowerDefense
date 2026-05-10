#pragma once

#include "rendu.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include <iostream>

/**
 * @brief Gestionnaire centralisé des textures du jeu.
 *
 * TextureManager charge les images depuis les fichiers, les stocke avec un
 * identifiant textuel, puis permet aux autres classes de récupérer les textures.
 *
 * Les classes comme Tour, Ennemi ou Carte ne possèdent pas les textures :
 * elles utilisent seulement des pointeurs non propriétaires vers les textures
 * stockées ici.
 */
class TextureManager {
public:
    void charger(const std::string& id, const std::string& chemin, Rendu& rendu) {
        SDL_Texture* tex = IMG_LoadTexture(rendu.getNativeRenderer(), chemin.c_str());
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