#pragma once

#include <vector>
#include <string>
#include "../core/rendu.hpp"
#include "case.hpp"

class Carte {
    public :  
    Carte(const std::string& filepath);
    void render(Rendu& rendu); // On dessine la carte
    private : 
    std::vector<std::vector<Case>> magrille;
    int m_Case_Taille = 40;
};