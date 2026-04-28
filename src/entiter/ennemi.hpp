#pragma once

#include "entite.hpp"
#include "../core/vec2.hpp"

#include <vector>
#include <cstddef>

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
    TypeEnnemi m_type;

    float m_vitesse = 0.0f;

    int m_pv = 0;
    int m_pvMax = 0;

    float m_resistance = 0.0f;

    bool m_volant = false;
    bool m_estArrive = false;

    std::size_t m_pointActuel = 0;

    // Sert aux tours pour savoir quel ennemi est le plus proche de la base.
    // Exemple : point 3 + progression 0.5 = progression totale 3.5.
    float m_progressionSegment = 0.0f;

public:
    Ennemi(float x, float y, TypeEnnemi type);

    void initialiserStats();

    void update(float dt) override;
    void update(float dt, const std::vector<Vec2>& chemin);

    void render(Rendu& rendu) const override;

    void prendreDegat(int degat);

    bool estMort() const;
    bool estArrive() const;
    bool estVolant() const;

    TypeEnnemi getType() const;
    int getPV() const;

    float  getX() const;
    float  getY() const;

    std::size_t getPointActuel() const;
    float getProgressionChemin() const;
};