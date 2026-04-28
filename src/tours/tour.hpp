#pragma once

#include "../core/rendu.hpp"
#include "../entiter/ennemi.hpp"
#include "../entiter/projectile.hpp"

#include <memory>
#include <optional>
#include <vector>

class Tour
{
protected:
    int gridX_;
    int gridY_;

    int degat_;
    float portee_;

    float delaiAttaque_;
    float timerAttaque_;

    float vitesseProjectile_;

    int cout_;

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

    virtual void update(
        float dt,
        std::vector<std::unique_ptr<Ennemi>>& ennemis,
        std::vector<Projectile>& projectiles,
        int tailleCase
    );

    virtual void render(Rendu& rendu, int tailleCase) const = 0;

    virtual bool peutCibler(const Ennemi& ennemi) const;

    bool estDansPortee(const Ennemi& ennemi, int tailleCase) const;

    std::optional<std::size_t> trouverIndexCible(
        const std::vector<std::unique_ptr<Ennemi>>& ennemis,
        int tailleCase
    ) const;

    void creerProjectileVers(
        const Ennemi& ennemi,
        std::vector<Projectile>& projectiles,
        int tailleCase
    ) const;

    int getGridX() const;
    int getGridY() const;
    int getCout() const;
};