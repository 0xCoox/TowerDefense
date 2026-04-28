#pragma once

#include "../core/window.hpp"
#include "../core/rendu.hpp"
#include "../core/input_manager.hpp"
#include "../core/joueur.hpp"

#include "../carte/carte.hpp"

#include "../entiter/ennemi.hpp"
#include "../entiter/projectile.hpp"

#include "../waves/wave_manager.hpp"

#include "../tours/tour.hpp"

#include "hud.hpp"

#include <chrono>
#include <memory>
#include <vector>

class Jeu
{
private:
    Window window_;
    Rendu rendu_;
    Carte carte_;
    InputManager input_;
    Hud hud_;

    bool estLance_;
    bool estPause_;

    Joueur joueur_;
    WaveManager waveManager_;

    int numeroVague_;

    int curseurX_;
    int curseurY_;
    int typeTourSelectionne_;

    std::vector<std::unique_ptr<Ennemi>> ennemis_;
    std::vector<std::unique_ptr<Tour>> tours_;
    std::vector<Projectile> projectiles_;

    std::chrono::steady_clock::time_point dernierTemps_;

public:
    Jeu();

    void lancer();

private:
    void traiterEntrees();
    void mettreAJour(float dt);
    void dessiner();

    void selectionnerTour(int typeTour);
    void essayerAjouterTour();

    void mettreAJourEnnemis(float dt);
    void mettreAJourTours(float dt);
    void mettreAJourProjectiles(float dt);

    void gererEnnemisMortsEtArrives();

    bool tourExisteDeja(int gridX, int gridY) const;

    void afficherCommandes() const;
};