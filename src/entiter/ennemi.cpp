#include "ennemi.hpp"
#include "../core/rendu.hpp"

#include <SDL2/SDL.h>
#include <cmath>

Ennemi::Ennemi(float x, float y, TypeEnnemi type)
    : Entite(x, y, TypeEntite::Ennemi),
      type_(type),     
      texture_(nullptr), 
      angle_(0.0f)      
{
    initialiserStats();
}

void Ennemi::initialiserStats()
{
    switch (type_)
    {
        case TypeEnnemi::Regular:
            vitesse_ = 70.0f;
            pv_ = 100;
            resistance_ = 0.0f;
            volant_ = false;
            break;

        case TypeEnnemi::Fast:
            vitesse_ = 130.0f;
            pv_ = 60;
            resistance_ = 0.0f;
            volant_ = false;
            break;

        case TypeEnnemi::Strong:
            vitesse_ = 45.0f;
            pv_ = 250;
            resistance_ = 0.0f;
            volant_ = false;
            break;

        case TypeEnnemi::Armored:
            vitesse_ = 50.0f;
            pv_ = 180;
            resistance_ = 0.5f;
            volant_ = false;
            break;

        case TypeEnnemi::Heli:
            vitesse_ = 80.0f;
            pv_ = 120;
            resistance_ = 0.0f;
            volant_ = true;
            break;

        case TypeEnnemi::Jet:
            vitesse_ = 170.0f;
            pv_ = 80;
            resistance_ = 0.0f;
            volant_ = true;
            break;
    }

    pvMax_ = pv_;
}

void Ennemi::update(float dt)
{
    // Cette fonction existe pour respecter la classe entite; dans le jeu, on utilise update(dt, chemin).
    (void)dt;
}

void Ennemi::appliquerRalentissement(float coeff, float duree)
{
    multiplicateurVitesse_ *= coeff;
    timerRalentissement_ = std::max(timerRalentissement_, duree);
    //Pour eviter d'avoir des cibles a l'arret 
    if (multiplicateurVitesse_ < 0.2f) multiplicateurVitesse_ = 0.2f;
}

void Ennemi::update(float dt, const std::vector<Vec2>& chemin)
{
    if (chemin.empty() || estArrive_) return;
    // Gestion du ralentissement
    if (timerRalentissement_ > 0) {
        timerRalentissement_ -= dt;
        if (timerRalentissement_ <= 0) {
            timerRalentissement_ = 0;
            multiplicateurVitesse_ = 1.0f; 
        }
    }
    // application ralentissement
    float vitesseReel = vitesse_ * multiplicateurVitesse_; 

    if (pointActuel_ >= chemin.size()) {
        estArrive_ = true;
        return;
    }

    Vec2 cible = chemin[pointActuel_];
    float dx = cible.x - x_;
    float dy = cible.y - y_;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < 2.0f) {
        pointActuel_++;
        progressionSegment_ = 0.0f;
        return;
    }

    float directionX = dx / distance;
    float directionY = dy / distance;
    angle_ = std::atan2(directionY, directionX) * (180.0f / M_PI);


    float distanceAParcourir = vitesseReel * dt;
    
    if (distanceAParcourir >= distance) {
        x_ = cible.x;
        y_ = cible.y;
        pointActuel_++;
        progressionSegment_ = 0.0f;
    } else {
        x_ += directionX * distanceAParcourir;
        y_ += directionY * distanceAParcourir;
        if (distance > 0.001f) {
            progressionSegment_ += distanceAParcourir / distance;
        }
    }
}

void Ennemi::render(Rendu& rendu) const
{
    int tailleAffichage = 50; 
    int moitie = tailleAffichage / 2;

    SDL_Rect rect = {
        static_cast<int>(x_ - moitie),
        static_cast<int>(y_ - moitie),
        tailleAffichage,
        tailleAffichage
    };

    if (texture_) 
    {
        float newAngle = angle_ + 90.0f;
        rendu.renderCopyEx(
            texture_,
            nullptr,
            &rect,
            newAngle,
            nullptr,
            SDL_FLIP_NONE
        );
    }
    else 
    {
        switch (type_)
        {
            case TypeEnnemi::Regular: rendu.setColor(255, 0, 0, 255); break;
            case TypeEnnemi::Fast:    rendu.setColor(255, 100, 100, 255); break;
            case TypeEnnemi::Strong:  rendu.setColor(120, 0, 0, 255); break;
            case TypeEnnemi::Armored: rendu.setColor(120, 120, 120, 255); break;
            case TypeEnnemi::Heli:    rendu.setColor(0, 200, 0, 255); break;
            case TypeEnnemi::Jet:     rendu.setColor(255, 255, 255, 255); break;
        }
        rendu.fillRect(rect);
    }

    SDL_Rect barreFond = { static_cast<int>(x_ - moitie), static_cast<int>(y_ - moitie - 10), tailleAffichage, 5 };
        rendu.setColor(80, 80, 80, 255);
        rendu.fillRect(barreFond);

        float ratioVie = std::fmax(0.0f, std::fmin(1.0f, (float)pv_ / pvMax_));
        SDL_Rect barreVie = {
            static_cast<int>(x_ - moitie),
            static_cast<int>(y_ - moitie - 10),
            static_cast<int>(tailleAffichage * ratioVie),
            5
        };
        rendu.setColor(0, 255, 0, 255);
        rendu.fillRect(barreVie);
}

void Ennemi::prendreDegat(int degat)
{
    float degatApresResistance = static_cast<float>(degat) * (1.0f - resistance_);

    pv_ -= static_cast<int>(degatApresResistance);

    if (pv_ < 0)
    {
        pv_ = 0;
    }
}
