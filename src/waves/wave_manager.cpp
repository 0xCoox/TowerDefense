#include "wave_manager.hpp"

void WaveManager::lancerVague(int numeroVague)
{
    if (m_active)
    {
        return;
    }

    m_active = true;
    m_numeroVague = numeroVague;

    m_ennemisRestants = 5 + numeroVague * 2;
    m_timerSpawn = 0.0f;

    if (numeroVague < 5)
    {
        m_delaiSpawn = 0.8f;
    }
    else
    {
        m_delaiSpawn = 0.5f;
    }
}

void WaveManager::update(
    float dt,
    std::vector<std::unique_ptr<Ennemi>>& ennemis,
    const std::vector<Vec2>& chemin
)
{
    if (!m_active)
    {
        return;
    }

    if (chemin.empty())
    {
        return;
    }

    if (m_ennemisRestants <= 0)
    {
        m_active = false;
        return;
    }

    m_timerSpawn += dt;

    if (m_timerSpawn >= m_delaiSpawn)
    {
        m_timerSpawn = 0.0f;

        Vec2 spawn = chemin.front();
        TypeEnnemi type = choisirTypeEnnemi();

        ennemis.push_back(
            std::make_unique<Ennemi>(spawn.x, spawn.y, type)
        );

        m_ennemisRestants--;
    }
}

bool WaveManager::vagueActive() const
{
    return m_active;
}

TypeEnnemi WaveManager::choisirTypeEnnemi() const
{
    if (m_numeroVague % 6 == 0)
    {
        return TypeEnnemi::Jet;
    }

    if (m_numeroVague % 5 == 0)
    {
        return TypeEnnemi::Armored;
    }

    if (m_numeroVague % 4 == 0)
    {
        return TypeEnnemi::Heli;
    }

    if (m_numeroVague % 3 == 0)
    {
        return TypeEnnemi::Fast;
    }

    if (m_numeroVague % 2 == 0)
    {
        return TypeEnnemi::Strong;
    }

    return TypeEnnemi::Regular;
}