#pragma once

#include "../entiter/ennemi.hpp"
#include "../core/vec2.hpp"

#include <vector>
#include <memory>

class WaveManager
{
public:
    WaveManager() = default;

    void lancerVague(int numeroVague);

    void update(
        float dt,
        std::vector<std::unique_ptr<Ennemi>>& ennemis,
        const std::vector<Vec2>& chemin
    );

    bool vagueActive() const { return active_; }

private:
    TypeEnnemi choisirTypeEnnemi() const;

private:
    bool active_ = false;

    int numeroVague_ = 0;
    int ennemisRestants_ = 0;

    float timerSpawn_ = 0.0f;
    float delaiSpawn_ = 0.8f;
};