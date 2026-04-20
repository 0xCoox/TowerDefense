#include "carte.hpp"
#include <fstream>
#include <iostream>

Carte::Carte(const std::string& filechemin) {
    std::ifstream fichier(filechemin);
    std::string ligne;

    if (!fichier.is_open()) {
        std::cerr << "Impossible d'ouvrir la map !" << std::endl;
        return;
    }

    int y = 0; 
    
    while (std::getline(fichier, ligne)) {
        std::vector<Case> colonne;
        int x = 0;
        for (char c : ligne) {
            Case t;
            t.x = x; 
            t.y = y; 
            if (c == '#') t.type = CaseType::Wall;
            else if (c == '.') t.type = CaseType::Chemin;
            else if (c == 'S') t.type = CaseType::Spawn;
            else if (c == 'E') t.type = CaseType::Base;
            else if (c == '@') t.type = CaseType::TowerSpace;
            
            colonne.push_back(t);
            
            x++;
        }
        magrille.push_back(colonne);    
        y++; 
    }
}

void Carte::graphisme(Rendu& rendu) {
    for (size_t y = 0; y < magrille.size(); ++y) {
        for (size_t x = 0; x < magrille[y].size(); ++x) {    
            SDL_Rect rect = { 
                static_cast<int>(x) * m_Case_Taille, 
                static_cast<int>(y) * m_Case_Taille, 
                m_Case_Taille, 
                m_Case_Taille 
            };      
            switch (magrille[y][x].type) {
                case CaseType::Wall:  
                    rendu.setColor(50, 50, 50, 255);
                    break;
                case CaseType::Chemin:  
                    rendu.setColor(100, 100, 100, 255); 
                    break;
                case CaseType::Spawn: 
                    rendu.setColor(0, 255, 0, 255);
                    break;
                case CaseType::Base:  
                    rendu.setColor(255, 0, 0, 255);
                    break;
                case CaseType::TowerSpace: 
                    rendu.setColor(150, 150, 200, 255); 
                    break;
            }     
            SDL_RenderFillRect(rendu.getNativeRenderer(), &rect);
        }
    }
}