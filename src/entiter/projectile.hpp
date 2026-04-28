#pragma once

#include "../core/rendu.hpp"

class Projectile
{
private:
    float x_;
    float y_;

    float cibleX_;
    float cibleY_;

    float vitesse_;
    bool termine_;

public:
    Projectile(float xDepart, float yDepart, float cibleX, float cibleY);

    void update(float dt);
    void render(Rendu& rendu) const;

    bool estTermine() const;
};