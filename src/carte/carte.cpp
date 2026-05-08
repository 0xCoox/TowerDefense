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

            if (c == '#') {
                t.type = CaseType::Wall;
            }
            else if (c == '.') {
                t.type = CaseType::Chemin;
            }
            else if (c == 'S') {
                t.type = CaseType::Spawn;
            }
            else if (c == 'E') {
                t.type = CaseType::Base;
            }
            else if (c == '@') {
                t.type = CaseType::TowerSpace;
            }
            else {
                t.type = CaseType::Wall;
            }

            colonne.push_back(t);
            x++;
        }

        grille_.push_back(colonne);
        y++;
    }

    calculerChemin();

    std::cout << "Chemin trouve : " << chemin_.size() << " points" << std::endl;
}

void Carte::graphisme(Rendu& rendu, SDL_Texture* tileset, SDL_Texture* baseTour) {
    const int ASSET_SIZE = 128; 

    for (size_t y = 0; y < grille_.size(); ++y) {
        for (size_t x = 0; x < grille_[y].size(); ++x) {
            
            SDL_Rect destRect = {
                static_cast<int>(x) * m_Case_Taille,
                static_cast<int>(y) * m_Case_Taille,
                m_Case_Taille,
                m_Case_Taille
            };

            if (tileset) {
                SDL_Rect srcRectMap = { 0, 0, ASSET_SIZE, ASSET_SIZE };
                double angle = 0.0;

                if (estCaseDeChemin(x, y)) {
                    bool H = estCaseDeChemin(x, (int)y - 1);
                    bool B = estCaseDeChemin(x, (int)y + 1);
                    bool G = estCaseDeChemin((int)x - 1, y);
                    bool D = estCaseDeChemin((int)x + 1, y);

                    if ((G && D) || (G && !H && !B) || (D && !H && !B)) {
                        srcRectMap.x = 3 * ASSET_SIZE; angle = 90.0;
                    } else if ((H && B) || (H && !G && !D) || (B && !G && !D)) {
                        srcRectMap.x = 3 * ASSET_SIZE; angle = 0.0;
                    } else {
                        srcRectMap.x = 4 * ASSET_SIZE;
                        if (B && D) angle = 0.0;
                        else if (B && G) angle = 90.0;
                        else if (H && G) angle = 180.0;
                        else if (H && D) angle = 270.0;
                    }
                } else {
                    srcRectMap.x = 0; // Neige
                }

                SDL_RenderCopyEx(rendu.getNativeRenderer(), tileset, &srcRectMap, &destRect, angle, NULL, SDL_FLIP_NONE);
            }

            if (grille_[y][x].type == CaseType::Spawn) {
                rendu.setColor(0, 255, 0, 100); 
                SDL_SetRenderDrawBlendMode(rendu.getNativeRenderer(), SDL_BLENDMODE_BLEND);
                SDL_RenderFillRect(rendu.getNativeRenderer(), &destRect);
            } 
            else if (grille_[y][x].type == CaseType::Base) {
                rendu.setColor(255, 0, 0, 100);
                SDL_SetRenderDrawBlendMode(rendu.getNativeRenderer(), SDL_BLENDMODE_BLEND);
                SDL_RenderFillRect(rendu.getNativeRenderer(), &destRect);
            }

            if (grille_[y][x].type == CaseType::TowerSpace && baseTour) {
                SDL_Rect srcRectBase = { 0, 128, ASSET_SIZE, ASSET_SIZE };
                SDL_RenderCopy(rendu.getNativeRenderer(), baseTour, &srcRectBase, &destRect);
            }
        }
    }
}

bool Carte::estDansLaCarte(int x, int y) const
{
    if (y < 0 || y >= static_cast<int>(grille_.size()))
    {
        return false;
    }

    if (x < 0 || x >= static_cast<int>(grille_[y].size()))
    {
        return false;
    }

    return true;
}

bool Carte::estCaseDeChemin(int x, int y) const
{
    if (!estDansLaCarte(x, y))
    {
        return false;
    }

    CaseType type = grille_[y][x].type;

    if (type == CaseType::Chemin ||
        type == CaseType::Spawn ||
        type == CaseType::Base)
    {
        return true;
    }

    return false;
}

void Carte::calculerChemin()
{
    chemin_.clear();

    int startX = -1;
    int startY = -1;

    // 1. Chercher le spawn S
    for (size_t y = 0; y < grille_.size(); ++y)
    {
        for (size_t x = 0; x < grille_[y].size(); ++x)
        {
            if (grille_[y][x].type == CaseType::Spawn)
            {
                startX = static_cast<int>(x);
                startY = static_cast<int>(y);
            }
        }
    }

    if (startX == -1 || startY == -1)
    {
        std::cerr << "Erreur : aucun spawn S trouve dans la carte." << std::endl;
        return;
    }

    std::vector<std::vector<bool>> visite(
        grille_.size(),
        std::vector<bool>(grille_[0].size(), false)
    );

    int x = startX;
    int y = startY;

    bool cheminTermine = false;

    while (!cheminTermine)
    {
        Vec2 point;
        point.x = x * m_Case_Taille + m_Case_Taille / 2.0f;
        point.y = y * m_Case_Taille + m_Case_Taille / 2.0f;

        chemin_.push_back(point);
        visite[y][x] = true;

        if (grille_[y][x].type == CaseType::Base)
        {
            cheminTermine = true;
            break;
        }

        bool prochainTrouve = false;

        // Ordre de recherche : droite, bas, gauche, haut
        const int directionX[4] = {1, 0, -1, 0};
        const int directionY[4] = {0, 1, 0, -1};

        for (int i = 0; i < 4; ++i)
        {
            int voisinX = x + directionX[i];
            int voisinY = y + directionY[i];

            if (estCaseDeChemin(voisinX, voisinY) && !visite[voisinY][voisinX])
            {
                x = voisinX;
                y = voisinY;
                prochainTrouve = true;
                break;
            }
        }

        if (!prochainTrouve)
        {
            std::cerr << "Erreur : chemin interrompu avant la base." << std::endl;
            cheminTermine = true;
        }
    }
}

const std::vector<Vec2>& Carte::getChemin() const
{
    return chemin_;
}

int Carte::getTailleCase() const
{
    return m_Case_Taille;
}

bool Carte::estConstructible(int x, int y) const
{
    if (!estDansLaCarte(x, y))
    {
        return false;
    }

    return grille_[y][x].type == CaseType::TowerSpace;
}