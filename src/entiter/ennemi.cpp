#include "ennemi.hpp"
#include "../core/rendu.hpp"

#include <SDL2/SDL.h>
#include <cmath>

Ennemi::Ennemi(float x, float y, TypeEnnemi type)
    : Entite(x, y, TypeEntite::Ennemi),
      m_type(type),     
      m_texture(nullptr), 
      m_angle(0.0f)      
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
    // Cette fonction existe pour respecter la classe entite; dans le jeu, on utilise update(dt, chemin).
    (void)dt;
}

void Ennemi::appliquerRalentissement(float coeff, float duree)
{
    m_multiplicateurVitesse *= coeff;
    m_timerRalentissement = std::max(m_timerRalentissement, duree);
    //Pour eviter d'avoir des cibles a l'arret 
    if (m_multiplicateurVitesse < 0.2f) m_multiplicateurVitesse = 0.2f;
}

void Ennemi::update(float dt, const std::vector<Vec2>& chemin)
{
    if (chemin.empty() || m_estArrive) return;
    // Gestion du ralentissement
    if (m_timerRalentissement > 0) {
        m_timerRalentissement -= dt;
        if (m_timerRalentissement <= 0) {
            m_timerRalentissement = 0;
            m_multiplicateurVitesse = 1.0f; 
        }
    }
    // application ralentissement
    float vitesseReel = m_vitesse * m_multiplicateurVitesse; 

    if (m_pointActuel >= chemin.size()) {
        m_estArrive = true;
        return;
    }

    Vec2 cible = chemin[m_pointActuel];
    float dx = cible.x - m_x;
    float dy = cible.y - m_y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < 2.0f) {
        m_pointActuel++;
        m_progressionSegment = 0.0f;
        return;
    }

    float directionX = dx / distance;
    float directionY = dy / distance;
    m_angle = std::atan2(directionY, directionX) * (180.0f / M_PI);


    float distanceAParcourir = vitesseReel * dt;
    
    if (distanceAParcourir >= distance) {
        m_x = cible.x;
        m_y = cible.y;
        m_pointActuel++;
        m_progressionSegment = 0.0f;
    } else {
        m_x += directionX * distanceAParcourir;
        m_y += directionY * distanceAParcourir;
        if (distance > 0.001f) {
            m_progressionSegment += distanceAParcourir / distance;
        }
    }
}

void Ennemi::render(Rendu& rendu) const
{
    int tailleAffichage = 50; 
    int moitie = tailleAffichage / 2;

    SDL_Rect rect = {
        static_cast<int>(m_x - moitie),
        static_cast<int>(m_y - moitie),
        tailleAffichage,
        tailleAffichage
    };

    if (m_texture) 
    {
        float newAngle = m_angle + 90.0f;
        SDL_RenderCopyEx(
            rendu.getNativeRenderer(),
            m_texture,
            nullptr,    
            &rect,        
            newAngle,      
            nullptr,      
            SDL_FLIP_NONE
        );
    }
    else 
    {
        switch (m_type)
        {
            case TypeEnnemi::Regular: rendu.setColor(255, 0, 0, 255); break;
            case TypeEnnemi::Fast:    rendu.setColor(255, 100, 100, 255); break;
            case TypeEnnemi::Strong:  rendu.setColor(120, 0, 0, 255); break;
            case TypeEnnemi::Armored: rendu.setColor(120, 120, 120, 255); break;
            case TypeEnnemi::Heli:    rendu.setColor(0, 200, 0, 255); break;
            case TypeEnnemi::Jet:     rendu.setColor(255, 255, 255, 255); break;
        }
        SDL_RenderFillRect(rendu.getNativeRenderer(), &rect);
    }

    SDL_Rect barreFond = { static_cast<int>(m_x - moitie), static_cast<int>(m_y - moitie - 10), tailleAffichage, 5 };
        rendu.setColor(80, 80, 80, 255);
        SDL_RenderFillRect(rendu.getNativeRenderer(), &barreFond);

        float ratioVie = std::fmax(0.0f, std::fmin(1.0f, (float)m_pv / m_pvMax));
        SDL_Rect barreVie = {
            static_cast<int>(m_x - moitie),
            static_cast<int>(m_y - moitie - 10),
            static_cast<int>(tailleAffichage * ratioVie),
            5
        };
        rendu.setColor(0, 255, 0, 255);
        SDL_RenderFillRect(rendu.getNativeRenderer(), &barreVie);
}

void Ennemi::prendreDegat(int degat)
{
    float degatApresResistance = static_cast<float>(degat) * (1.0f - m_resistance);

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

float Ennemi::getX() const
{
    return m_x;
}

float Ennemi::getY() const
{
    return m_y;
}

std::size_t Ennemi::getPointActuel() const
{
    return m_pointActuel;
}

float Ennemi::getProgressionChemin() const
{
    return static_cast<float>(m_pointActuel) + m_progressionSegment;
}