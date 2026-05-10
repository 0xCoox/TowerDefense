#include "jeu.hpp"

#include "game_config.hpp"

#include <SDL2/SDL.h>

#include <iostream>
#include <memory>
#include <string>

namespace
{
    constexpr TypeTour TYPE_TOUR_PAR_DEFAUT = TypeTour::Basique;

    constexpr int CURSEUR_X_INITIAL = 0;
    constexpr int CURSEUR_Y_INITIAL = 0;

    constexpr int TAILLE_POLICE_HUD = 24;

    const std::string CHEMIN_POLICE_HUD =
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
}

Jeu::Jeu()
    : window_(
          "Tower Defense",
          GameConfig::LARGEUR_FENETRE,
          GameConfig::HAUTEUR_FENETRE
      ),
      rendu_(window_.getNativeWindow()),
      input_(),
      hud_(CHEMIN_POLICE_HUD, TAILLE_POLICE_HUD),
      estLance_(true),
      estPause_(false),
      world_(
          "../assets/map.txt",
          GameConfig::ARGENT_INITIAL,
          GameConfig::VIES_INITIALES,
          GameConfig::PREMIERE_VAGUE
      ),
      textureManager_(),
      guiManager_(),
      gameRenderer_(),
      interactionHandler_(
          TYPE_TOUR_PAR_DEFAUT,
          CURSEUR_X_INITIAL,
          CURSEUR_Y_INITIAL
      ),
      dernierTemps_(std::chrono::steady_clock::now())
{
    textureManager_.charger(
        "ennemi_regular",
        "../assets/ground_shaker_asset/Blue/Bodies/body_tracks.png",
        rendu_
    );

    textureManager_.charger(
        "ennemi_fast",
        "../assets/ground_shaker_asset/Purple/Bodies/body_tracks.png",
        rendu_
    );

    textureManager_.charger(
        "ennemi_strong",
        "../assets/ground_shaker_asset/Camo/Bodies/body_tracks.png",
        rendu_
    );

    textureManager_.charger(
        "ennemi_armored",
        "../assets/ground_shaker_asset/Red/Bodies/body_tracks.png",
        rendu_
    );

    textureManager_.charger(
        "ennemi_heli",
        "../assets/ground_shaker_asset/Blue/Bodies/av2.png",
        rendu_
    );

    textureManager_.charger(
        "ennemi_jet",
        "../assets/ground_shaker_asset/Blue/Bodies/av.png",
        rendu_
    );

    textureManager_.charger(
        "weapons_purple",
        "../assets/ground_shaker_asset/Purple/Weapons/weapons.png",
        rendu_
    );

    textureManager_.charger(
        "weapons_blue",
        "../assets/ground_shaker_asset/Blue/Weapons/weapons.png",
        rendu_
    );

    textureManager_.charger(
        "map_sprite",
        "../assets/ground_shaker_asset/Terrains/terrain.png",
        rendu_
    );

    textureManager_.charger(
        "base_tour",
        "../assets/ground_shaker_asset/Purple/Towers/towers_walls_snow_1.png",
        rendu_
    );

    SDL_Color couleurAmeliorer = {50, 200, 50, 255};
    SDL_Color couleurVague = {100, 100, 100, 255};
    SDL_Color couleurVendre = {200, 50, 50, 255};

    int xBouton = GameConfig::LARGEUR_MAP + 25;

    guiManager_.ajouterBoutton(
        std::make_unique<Boutton>(
            xBouton,
            150,
            150,
            40,
            "Ameliorer",
            couleurAmeliorer,
            [this]()
            {
                interactionHandler_.ameliorerTourSelectionnee(world_);
            }
        )
    );

    guiManager_.ajouterBoutton(
        std::make_unique<Boutton>(
            xBouton,
            200,
            150,
            40,
            "Vague",
            couleurVague,
            [this]()
            {
                world_.lancerVague();
            }
        )
    );

    guiManager_.ajouterBoutton(
        std::make_unique<Boutton>(
            xBouton,
            250,
            150,
            40,
            "Vendre",
            couleurVendre,
            [this]()
            {
                interactionHandler_.vendreTourSelectionnee(world_);
            }
        )
    );

    afficherCommandes();
}

void Jeu::lancer()
{
    while (estLance_)
    {
        auto tempsActuel = std::chrono::steady_clock::now();

        std::chrono::duration<float> tempsEcoule =
            tempsActuel - dernierTemps_;

        float dt = tempsEcoule.count();
        dernierTemps_ = tempsActuel;

        traiterEntrees();

        if (!estPause_)
        {
            mettreAJour(dt);
        }

        dessiner();
    }
}

void Jeu::traiterEntrees()
{
    interactionHandler_.traiterEntrees(
        input_,
        guiManager_,
        hud_,
        world_,
        textureManager_,
        estLance_,
        estPause_
    );
}

void Jeu::mettreAJour(float dt)
{
    world_.update(dt, textureManager_);

    if (world_.estJoueurMort())
    {
        std::cout << "Game Over !" << std::endl;
        estLance_ = false;
    }
}

void Jeu::dessiner()
{
    gameRenderer_.dessiner(
        rendu_,
        world_.carte(),
        textureManager_,
        guiManager_,
        hud_,
        world_.joueur(),
        world_.tours(),
        world_.ennemis(),
        world_.projectiles(),
        interactionHandler_.getCurseurX(),
        interactionHandler_.getCurseurY(),
        input_.getMouseX(),
        input_.getMouseY(),
        world_.numeroVague(),
        interactionHandler_.getTypeTourSelectionne(),
        interactionHandler_.estDragTourActif(),
        interactionHandler_.getDragTourType(),
        estPause_,
        interactionHandler_.doitAfficherPorteePlacement()
    );
}

void Jeu::afficherCommandes() const
{
    std::cout << "Commandes :" << std::endl;
    std::cout << "Fleches : deplacer le curseur" << std::endl;
    std::cout << "1 : tour basique" << std::endl;
    std::cout << "2 : tour sniper" << std::endl;
    std::cout << "3 : tour canon" << std::endl;
    std::cout << "4 : tour glace" << std::endl;
    std::cout << "5 : tour anti-air" << std::endl;
    std::cout << "A : placer une tour" << std::endl;
    std::cout << "ENTER : lancer une vague" << std::endl;
    std::cout << "Bouton Ameliorer : ameliorer la tour selectionnee" << std::endl;
    std::cout << "Bouton Vendre : vendre la tour selectionnee" << std::endl;
    std::cout << "Bouton Vague : lancer une vague" << std::endl;
    std::cout << "SPACE : pause" << std::endl;
    std::cout << "ESC : quitter" << std::endl;

    std::cout << "Argent initial : "
              << world_.joueur().getArgent()
              << std::endl;

    std::cout << "Vies initiales : "
              << world_.joueur().getVies()
              << std::endl;
}