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

private:
    bool estDansLaCarte(int x, int y) const;
    bool estCaseDeChemin(int x, int y) const;
    void calculerChemin();

private:
    std::vector<std::vector<Case>> magrille;
    std::vector<Vec2> m_chemin;

    int m_Case_Taille = 30;
};