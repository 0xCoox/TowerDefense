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

    bool vagueActive() const;

private:
    TypeEnnemi choisirTypeEnnemi() const;

private:
    bool m_active = false;

    int m_numeroVague = 0;
    int m_ennemisRestants = 0;

    float m_timerSpawn = 0.0f;
    float m_delaiSpawn = 0.8f;
};