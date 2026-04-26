#include "ennemi.hpp"
#include "../core/rendu.hpp"

#include <SDL2/SDL.h>
#include <cmath>

Ennemi::Ennemi(float x, float y, TypeEnnemi type)
    : Entite(x, y, TypeEntite::Ennemi),
      m_type(type)
{
    initialiserStats();
}

void Ennemi::initialiserStats()
{
    switch (m_type)
    {
        case TypeEnnemi::Regular:
            m_vitesse = 70.0f;
            m_pv = 100;
            m_resistance = 0.0f;
            m_volant = false;
            break;

        case TypeEnnemi::Fast:
            m_vitesse = 130.0f;
            m_pv = 60;
            m_resistance = 0.0f;
            m_volant = false;
            break;

        case TypeEnnemi::Strong:
            m_vitesse = 45.0f;
            m_pv = 250;
            m_resistance = 0.0f;
            m_volant = false;
            break;

        case TypeEnnemi::Armored:
            m_vitesse = 50.0f;
            m_pv = 180;
            m_resistance = 0.5f;
            m_volant = false;
            break;

        case TypeEnnemi::Heli:
            m_vitesse = 80.0f;
            m_pv = 120;
            m_resistance = 0.0f;
            m_volant = true;
            break;

        case TypeEnnemi::Jet:
            m_vitesse = 170.0f;
            m_pv = 80;
            m_resistance = 0.0f;
            m_volant = true;
            break;
    }

    m_pvMax = m_pv;
}

void Ennemi::update(float dt)
{
    // Cette fonction existe seulement pour respecter la classe Entite.
    // Dans le jeu, on utilise update(dt, chemin).
    (void)dt;
}

void Ennemi::update(float dt, const std::vector<Vec2>& chemin)
{
    if (chemin.empty())
    {
        return;
    }

    if (m_estArrive)
    {
        return;
    }

    if (m_pointActuel >= chemin.size())
    {
        m_estArrive = true;
        return;
    }

    Vec2 cible = chemin[m_pointActuel];

    float dx = cible.x - m_x;
    float dy = cible.y - m_y;

    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < 2.0f)
    {
        m_pointActuel++;

        if (m_pointActuel >= chemin.size())
        {
            m_estArrive = true;
        }

        return;
    }

    float directionX = dx / distance;
    float directionY = dy / distance;

    m_x += directionX * m_vitesse * dt;
    m_y += directionY * m_vitesse * dt;
}

void Ennemi::render(Rendu& rendu) const
{
    SDL_Rect rect = {
        static_cast<int>(m_x - 15),
        static_cast<int>(m_y - 15),
        30,
        30
    };

    switch (m_type)
    {
        case TypeEnnemi::Regular:
            rendu.setColor(255, 0, 0, 255);
            break;

        case TypeEnnemi::Fast:
            rendu.setColor(255, 100, 100, 255);
            break;

        case TypeEnnemi::Strong:
            rendu.setColor(120, 0, 0, 255);
            break;

        case TypeEnnemi::Armored:
            rendu.setColor(120, 120, 120, 255);
            break;

        case TypeEnnemi::Heli:
            rendu.setColor(0, 200, 0, 255);
            break;

        case TypeEnnemi::Jet:
            rendu.setColor(255, 255, 255, 255);
            break;
    }

    SDL_RenderFillRect(rendu.getNativeRenderer(), &rect);

    SDL_Rect barreFond = {
        static_cast<int>(m_x - 15),
        static_cast<int>(m_y - 22),
        30,
        4
    };

    rendu.setColor(80, 80, 80, 255);
    SDL_RenderFillRect(rendu.getNativeRenderer(), &barreFond);

    float ratioVie = static_cast<float>(m_pv) / static_cast<float>(m_pvMax);

    if (ratioVie < 0.0f)
    {
        ratioVie = 0.0f;
    }

    SDL_Rect barreVie = {
        static_cast<int>(m_x - 15),
        static_cast<int>(m_y - 22),
        static_cast<int>(30.0f * ratioVie),
        4
    };

    rendu.setColor(0, 255, 0, 255);
    SDL_RenderFillRect(rendu.getNativeRenderer(), &barreVie);
}

void Ennemi::prendreDegat(int degat)
{
    float degatApresResistance = degat * (1.0f - m_resistance);

    m_pv -= static_cast<int>(degatApresResistance);

    if (m_pv < 0)
    {
        m_pv = 0;
    }
}

bool Ennemi::estMort() const
{
    return m_pv <= 0;
}

bool Ennemi::estArrive() const
{
    return m_estArrive;
}

bool Ennemi::estVolant() const
{
    return m_volant;
}

TypeEnnemi Ennemi::getType() const
{
    return m_type;
}

int Ennemi::getPV() const
{
    return m_pv;
}