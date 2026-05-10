#pragma once

#include "../carte/carte.hpp"
#include "../core/joueur.hpp"
#include "../core/texture.hpp"
#include "../entiter/ennemi.hpp"
#include "../entiter/projectile.hpp"
#include "../tours/tour.hpp"
#include "../tours/type_tour.hpp"
#include "../waves/wave_manager.hpp"

#include <memory>
#include <optional>
#include <vector>

class GameWorld
{
public:
    GameWorld(
        const std::string& cheminCarte,
        int argentInitial,
        int viesInitiales,
        int premiereVague
    );

    void update(float dt, TextureManager& textureManager);

    std::optional<int> preparerAchatTour(
        TypeTour typeTour,
        TextureManager& textureManager
    );

    bool placerTour(
        TypeTour typeTour,
        int gridX,
        int gridY,
        TextureManager& textureManager
    );

    bool placerTourDejaPayee(
        TypeTour typeTour,
        int gridX,
        int gridY,
        TextureManager& textureManager
    );

    bool ameliorerTour(int gridX, int gridY);
    bool vendreTour(int gridX, int gridY);
    void lancerVague();

    int trouverIndexTour(int gridX, int gridY) const;
    bool tourExisteDeja(int gridX, int gridY) const;

    Carte& carte() { return carte_; }
    const Carte& carte() const { return carte_; }

    Joueur& joueur() { return joueur_; }
    const Joueur& joueur() const { return joueur_; }

    WaveManager& waveManager() { return waveManager_; }

    std::vector<std::unique_ptr<Ennemi>>& ennemis() { return ennemis_; }
    const std::vector<std::unique_ptr<Ennemi>>& ennemis() const { return ennemis_; }

    std::vector<std::unique_ptr<Tour>>& tours() { return tours_; }
    const std::vector<std::unique_ptr<Tour>>& tours() const { return tours_; }

    std::vector<Projectile>& projectiles() { return projectiles_; }
    const std::vector<Projectile>& projectiles() const { return projectiles_; }

    int numeroVague() const { return numeroVague_; }
    void incrementerVague() { numeroVague_++; }

    bool estJoueurMort() const { return joueur_.estMort(); }

private:
    void mettreAJourEnnemis(float dt);
    void mettreAJourTours(float dt);
    void mettreAJourProjectiles(float dt);
    void gererEnnemisMortsEtArrives(int argentParEnnemi);

    Carte carte_;
    Joueur joueur_;
    WaveManager waveManager_;
    std::vector<std::unique_ptr<Ennemi>> ennemis_;
    std::vector<std::unique_ptr<Tour>> tours_;
    std::vector<Projectile> projectiles_;
    int numeroVague_;
};
