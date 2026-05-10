#pragma once

#include "entite.hpp"
#include "../core/vec2.hpp"

#include <vector>
#include <cstddef>
#include <SDL2/SDL.h> 

class Rendu;

enum class TypeEnnemi
{
    Regular,
    Fast,
    Strong,
    Armored,
    Heli,
    Jet
};

class Ennemi : public Entite
{
private:
    TypeEnnemi type_;

    float vitesse_ = 0.0f;

    int pv_ = 0;
    int pvMax_ = 0;

    float resistance_ = 0.0f;

    bool volant_ = false;
    bool estArrive_ = false;

    std::size_t pointActuel_ = 0;

    // Sert aux tours pour savoir quel ennemi est le plus proche de la base.
    // Exemple : point 3 + progression 0.5 = progression totale 3.5.
    float progressionSegment_ = 0.0f;
    SDL_Texture* texture_; 
    float angle_;
    //Partie Slow quand on ets hit par une tour glace
    float multiplicateurVitesse_ = 1.0f; 
    float timerRalentissement_ = 0.0f;
public:
    void setTexture(SDL_Texture* tex) { texture_ = tex; }
    Ennemi(float x, float y, TypeEnnemi type);

    void initialiserStats();

    void update(float dt) override;
    void update(float dt, const std::vector<Vec2>& chemin);

    void render(Rendu& rendu) const override;

    void prendreDegat(int degat);
    void appliquerRalentissement(float coeff, float duree);
    
    bool estMort() const { return pv_ <= 0; }
    bool estArrive() const { return estArrive_; }
    bool estVolant() const { return volant_; }

    TypeEnnemi getType() const { return type_; }
    int getPV() const { return pv_; }

    float getX() const { return x_; }
    float getY() const { return y_; }

    std::size_t getPointActuel() const { return pointActuel_; }
    float getProgressionChemin() const
    {
        return static_cast<float>(pointActuel_) + progressionSegment_;
    }
};