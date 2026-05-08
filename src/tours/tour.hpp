#pragma once

#include "../core/rendu.hpp"
#include "../entiter/ennemi.hpp"
#include "../entiter/projectile.hpp"
#include <SDL2/SDL.h>

#include <memory>
#include <optional>
#include <vector>

class Tour
{
protected:
    // Position et stats
    int gridX_;
    int gridY_;
    int degat_;
    float portee_;
    float delaiAttaque_;
    float timerAttaque_;
    float vitesseProjectile_;
    int cout_;
    float angle_; 
// Faut que je clean le code Base est maintenant useless on ne load plus que un canon 
    SDL_Texture* textureBase_ = nullptr;  
    SDL_Texture* textureCanon_ = nullptr;
    int spriteX_ = 0; 
    int spriteY_ = 0; 
    const int SPRITE_SIZE = 96; 

public:
    Tour(
        int gridX, 
        int gridY, 
        int degat, 
        float portee, 
        float delaiAttaque, 
        float vitesseProjectile, 
        int cout
    );

    virtual ~Tour() = default;

    void setCanonStyle(
        SDL_Texture* tex, 
        int col, 
        int row) 
        {
        textureCanon_ = tex; 
        spriteX_ = col * SPRITE_SIZE;
        spriteY_ = row * SPRITE_SIZE;
    }

    void setTextures(
        SDL_Texture* base, 
        SDL_Texture* canon
    ) {
        textureBase_ = base;
        textureCanon_ = canon;
    }

    virtual void update(
        float dt, 
        std::vector<std::unique_ptr<Ennemi>>& ennemis,
        std::vector<Projectile>& projectiles, 
        int tailleCase
    );
    
    virtual void render(
        Rendu& rendu, 
        int tailleCase
    ) const;

    virtual bool peutCibler(const Ennemi& ennemi) const;
    bool estDansPortee(
        const Ennemi& ennemi, 
        int tailleCase
    ) const;
    std::optional<std::size_t> trouverIndexCible(
        const std::vector<std::unique_ptr<Ennemi>>& ennemis,
        int tailleCase
    ) const;
    void creerProjectileVers(
        const Ennemi& ennemi, 
        std::vector<Projectile>& projectiles,
        int tailleCase) const;

    int getGridX() const;
    int getGridY() const;
    int getCout() const;
    float getAngle() const { return angle_; }
};