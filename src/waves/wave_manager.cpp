#include "wave_manager.hpp"

void WaveManager::lancerVague(int numeroVague)
{
    if (active_)
    {
        return;
    }

    active_ = true;
    numeroVague_ = numeroVague;

    ennemisRestants_ = 5 + numeroVague * 2;
    timerSpawn_ = 0.0f;

    if (numeroVague < 5)
    {
        delaiSpawn_ = 0.8f;
    }
    else
    {
        delaiSpawn_ = 0.5f;
    }
}

void WaveManager::update(
    float dt,
    std::vector<std::unique_ptr<Ennemi>>& ennemis,
    const std::vector<Vec2>& chemin
)
{
    if (!active_)
    {
        return;
    }

    if (chemin.empty())
    {
        return;
    }

    if (ennemisRestants_ <= 0)
    {
        active_ = false;
        return;
    }

    timerSpawn_ += dt;

    if (timerSpawn_ >= delaiSpawn_)
    {
        timerSpawn_ = 0.0f;

        Vec2 spawn = chemin.front();
        TypeEnnemi type = choisirTypeEnnemi();

        ennemis.push_back(
            std::make_unique<Ennemi>(spawn.x, spawn.y, type)
        );

        ennemisRestants_--;
    }
}

TypeEnnemi WaveManager::choisirTypeEnnemi() const
{
    if (numeroVague_ % 6 == 0)
    {
        return TypeEnnemi::Jet;
    }

    if (numeroVague_ % 5 == 0)
    {
        return TypeEnnemi::Armored;
    }

    if (numeroVague_ % 4 == 0)
    {
        return TypeEnnemi::Heli;
    }

    if (numeroVague_ % 3 == 0)
    {
        return TypeEnnemi::Fast;
    }

    if (numeroVague_ % 2 == 0)
    {
        return TypeEnnemi::Strong;
    }

    return TypeEnnemi::Regular;
}