#pragma once

#include "../core/rendu.hpp"
#include "../entiter/ennemi.hpp"
#include "../entiter/projectile.hpp"

#include <SDL2/SDL.h>

#include <memory>
#include <optional>
#include <vector>
/**
 * @brief Classe mère de toutes les tours du jeu.
 *
 * Une tour possède une position sur la grille, des statistiques d'attaque,
 * un coût, un niveau d'amélioration et une texture de canon.
 *
 * Les classes filles comme TourBasique, TourSniper, TourCanon, TourGlace
 * et TourAntiAir définissent les valeurs spécifiques de chaque type de tour.
 */
class Tour
{
protected:
    // Position et stat
    int gridX_;
    int gridY_;
    int degat_;
    float portee_;
    float delaiAttaque_;
    float timerAttaque_;
    float vitesseProjectile_;
    float ralentissement_;
    float rayonSplash_;
    int cout_;
    float angle_;
    int idCibleVerrouille_;

    // Upgrade et vente
    int niveau_;
    int niveauMax_;
    int totalInvesti_;

    // Textures et sprite
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
        int row
    )
    {
        textureCanon_ = tex;
        spriteX_ = col * SPRITE_SIZE;
        spriteY_ = row * SPRITE_SIZE;
    }

    void setTextures(
        SDL_Texture* base,
        SDL_Texture* canon
    )
    {
        textureBase_ = base;
        textureCanon_ = canon;
    }
    /**
     * @brief Met à jour la tour pendant une frame.
     *
     * La tour cherche une cible valide, vérifie si cette cible est dans sa portée,
     * oriente son canon vers elle, puis crée un projectile si son délai d'attaque
     * est terminé.
     *
     * @param dt Temps écoulé depuis la dernière frame, en secondes.
     * @param ennemis Liste des ennemis actifs.
     * @param projectiles Liste des projectiles du jeu.
     * @param tailleCase Taille d'une case de la carte en pixels.
     */

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
        int tailleCase
    ) const;

    int getGridX() const { return gridX_; }
    int getGridY() const { return gridY_; }
    int getCout() const { return cout_; }

    bool peutAmeliorer() const { return niveau_ < niveauMax_; }
    /**
     * @brief Améliore la tour si elle n'a pas atteint son niveau maximum.
     *
     * L'amélioration augmente les statistiques de la tour, par exemple les dégâts,
     * la portée ou la vitesse des projectiles.
     *
     * @return true si l'amélioration a été effectuée, false sinon.
     */
    bool ameliorer();

    int getNiveau() const { return niveau_; }
    int getCoutAmelioration() const;
    int getPrixVente() const { return totalInvesti_ / 2; }
    float getPortee() const { return portee_; }
    float getAngle() const
    {
        return angle_;
    }
};