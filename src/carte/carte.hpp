#pragma once

#include <vector>
#include <string>

#include "../core/rendu.hpp"
#include "../core/vec2.hpp"
#include "case.hpp"

class Carte {
public:
    Carte(const std::string& filepath);

    void graphisme(Rendu& rendu);

    const std::vector<Vec2>& getChemin() const;
    int getTailleCase() const;

    bool estConstructible(int x, int y) const;

private:
    bool estDansLaCarte(int x, int y) const;
    bool estCaseDeChemin(int x, int y) const;
    void calculerChemin();

private:
    std::vector<std::vector<Case>> grille_;
    std::vector<Vec2> chemin_;

    int m_Case_Taille = 30;
};