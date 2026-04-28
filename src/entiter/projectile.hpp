#pragma once

#include "../core/rendu.hpp"
#include "ennemi.hpp"

#include <memory>
#include <vector>

class Projectile
{
private:
    float x_;
    float y_;

    int idCible_;
    int degat_;

    float vitesse_;
    bool termine_;

public:
    Projectile(
        float xDepart,
        float yDepart,
        int idCible,
        int degat,
        float vitesse
    );

    void update(
        float dt,
        std::vector<std::unique_ptr<Ennemi>>& ennemis
    );

    void render(Rendu& rendu) const;

    bool estTermine() const;
};