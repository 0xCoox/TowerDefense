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
public:
    Ennemi(float x, float y, TypeEnnemi type);

    // Obligatoire car Entite a update(float dt) = 0
    void update(float dt) override;

    // Version utilisée par le jeu pour suivre le chemin
    void update(float dt, const std::vector<Vec2>& chemin);

    void render(Rendu& rendu) const override;

    void prendreDegat(int degat);

    bool estMort() const;
    bool estArrive() const;
    bool estVolant() const;

    TypeEnnemi getType() const;
    int getPV() const;

private:
    void initialiserStats();

private:
    TypeEnnemi m_type;

    float m_vitesse = 0.0f;

    int m_pv = 0;
    int m_pvMax = 0;

    float m_resistance = 0.0f;
    bool m_volant = false;

    std::size_t m_pointActuel = 0;
    bool m_estArrive = false;
};