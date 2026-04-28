#include "core/window.hpp"
#include "carte/carte.hpp"
#include "core/rendu.hpp"
#include "core/input_manager.hpp"

#include "entiter/ennemi.hpp"
#include "entiter/projectile.hpp"

#include "waves/wave_manager.hpp"

#include "tours/tour.hpp"
#include "tours/tour_basique.hpp"
#include "tours/tour_sniper.hpp"
#include "tours/tour_canon.hpp"
#include "tours/tour_glace.hpp"
#include "tours/tour_anti_air.hpp"

#include <SDL2/SDL.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

static bool tourExisteDeja(
    const std::vector<std::unique_ptr<Tour>>& tours,
    int gridX,
    int gridY
)
{
    for (const auto& tour : tours)
    {
        if (tour->getGridX() == gridX && tour->getGridY() == gridY)
        {
            return true;
        }
    }

    return false;
}

static void ajouterTour(
    std::vector<std::unique_ptr<Tour>>& tours,
    const Carte& carte,
    int gridX,
    int gridY,
    int typeTour
)
{
    if (!carte.estConstructible(gridX, gridY))
    {
        std::cout << "Impossible : tu peux construire seulement sur les cases @"
                  << std::endl;
        return;
    }

    if (tourExisteDeja(tours, gridX, gridY))
    {
        std::cout << "Impossible : il y a deja une tour ici." << std::endl;
        return;
    }

    if (typeTour == 1)
    {
        tours.push_back(std::make_unique<TourBasique>(gridX, gridY));
        std::cout << "Tour basique ajoutee en "
                  << gridX << ", " << gridY << std::endl;
    }
    else if (typeTour == 2)
    {
        tours.push_back(std::make_unique<TourSniper>(gridX, gridY));
        std::cout << "Tour sniper ajoutee en "
                  << gridX << ", " << gridY << std::endl;
    }
    else if (typeTour == 3)
    {
        tours.push_back(std::make_unique<TourCanon>(gridX, gridY));
        std::cout << "Tour canon ajoutee en "
                  << gridX << ", " << gridY << std::endl;
    }
    else if (typeTour == 4)
    {
        tours.push_back(std::make_unique<TourGlace>(gridX, gridY));
        std::cout << "Tour glace ajoutee en "
                  << gridX << ", " << gridY << std::endl;
    }
    else if (typeTour == 5)
    {
        tours.push_back(std::make_unique<TourAntiAir>(gridX, gridY));
        std::cout << "Tour anti-air ajoutee en "
                  << gridX << ", " << gridY << std::endl;
    }
}

int main()
{
    try
    {
        Window gameWindow("Tower Defense", 1920, 1080);
        Rendu gameRendu(gameWindow.getNativeWindow());
        Carte myMap("assets/map.txt");

        InputManager input;

        bool isRunning = true;
        bool isPaused = false;

        std::vector<std::unique_ptr<Ennemi>> ennemis;
        std::vector<std::unique_ptr<Tour>> tours;
        std::vector<Projectile> projectiles;

        WaveManager waveManager;

        int numeroVague = 1;
        int viesJoueur = 20;

        int curseurX = 0;
        int curseurY = 0;
        int typeTourSelectionne = 1;

        auto referentialTime = std::chrono::steady_clock::now();

        std::cout << "Commandes :" << std::endl;
        std::cout << "Fleches : deplacer curseur" << std::endl;
        std::cout << "1 : tour basique" << std::endl;
        std::cout << "2 : tour sniper" << std::endl;
        std::cout << "3 : tour canon" << std::endl;
        std::cout << "4 : tour glace" << std::endl;
        std::cout << "5 : tour anti-air" << std::endl;
        std::cout << "A : placer une tour sur une case @" << std::endl;
        std::cout << "ENTER : lancer une vague" << std::endl;
        std::cout << "SPACE : pause" << std::endl;
        std::cout << "ESC : quitter" << std::endl;

        while (isRunning)
        {
            auto currentTime = std::chrono::steady_clock::now();

            std::chrono::duration<float> elapsedTime =
                currentTime - referentialTime;

            float dt = elapsedTime.count();
            referentialTime = currentTime;

            input.update();

            if (input.shouldQuit() || input.isKeyPressed(SDLK_ESCAPE))
            {
                isRunning = false;
            }

            if (input.isKeyPressed(SDLK_SPACE))
            {
                isPaused = !isPaused;

                if (isPaused)
                {
                    std::cout << "Pause" << std::endl;
                }
                else
                {
                    std::cout << "Reprise" << std::endl;
                }
            }

            if (input.isKeyPressed(SDLK_RETURN))
            {
                waveManager.lancerVague(numeroVague);
                std::cout << "Vague " << numeroVague << " lancee" << std::endl;
                numeroVague++;
            }

            if (input.isKeyPressed(SDLK_UP))
            {
                curseurY--;
            }

            if (input.isKeyPressed(SDLK_DOWN))
            {
                curseurY++;
            }

            if (input.isKeyPressed(SDLK_LEFT))
            {
                curseurX--;
            }

            if (input.isKeyPressed(SDLK_RIGHT))
            {
                curseurX++;
            }

            if (input.isKeyPressed(SDLK_1))
            {
                typeTourSelectionne = 1;
                std::cout << "Selection : Tour basique" << std::endl;
            }

            if (input.isKeyPressed(SDLK_2))
            {
                typeTourSelectionne = 2;
                std::cout << "Selection : Tour sniper" << std::endl;
            }

            if (input.isKeyPressed(SDLK_3))
            {
                typeTourSelectionne = 3;
                std::cout << "Selection : Tour canon" << std::endl;
            }

            if (input.isKeyPressed(SDLK_4))
            {
                typeTourSelectionne = 4;
                std::cout << "Selection : Tour glace" << std::endl;
            }

            if (input.isKeyPressed(SDLK_5))
            {
                typeTourSelectionne = 5;
                std::cout << "Selection : Tour anti-air" << std::endl;
            }

            if (input.isKeyPressed(SDLK_a))
            {
                ajouterTour(
                    tours,
                    myMap,
                    curseurX,
                    curseurY,
                    typeTourSelectionne
                );
            }

            if (!isPaused)
            {
                waveManager.update(dt, ennemis, myMap.getChemin());

                for (auto& ennemi : ennemis)
                {
                    ennemi->update(dt, myMap.getChemin());
                }

                for (auto& tour : tours)
                {
                    tour->update(
                        dt,
                        ennemis,
                        projectiles,
                        myMap.getTailleCase()
                    );
                }

                for (auto& projectile : projectiles)
                {
                    projectile.update(dt);
                }

                projectiles.erase(
                    std::remove_if(
                        projectiles.begin(),
                        projectiles.end(),
                        [](const Projectile& projectile)
                        {
                            return projectile.estTermine();
                        }
                    ),
                    projectiles.end()
                );

                int ennemisArrives = 0;

                for (const auto& ennemi : ennemis)
                {
                    if (ennemi->estArrive())
                    {
                        ennemisArrives++;
                    }
                }

                if (ennemisArrives > 0)
                {
                    viesJoueur -= ennemisArrives;

                    std::cout << ennemisArrives
                              << " ennemi(s) arrive(s). Vies restantes : "
                              << viesJoueur << std::endl;
                }

                ennemis.erase(
                    std::remove_if(
                        ennemis.begin(),
                        ennemis.end(),
                        [](const std::unique_ptr<Ennemi>& ennemi)
                        {
                            return ennemi->estMort() || ennemi->estArrive();
                        }
                    ),
                    ennemis.end()
                );

                if (viesJoueur <= 0)
                {
                    std::cout << "Game Over !" << std::endl;
                    isRunning = false;
                }
            }

            gameRendu.setColor(0, 0, 0, 255);
            gameRendu.clear();

            myMap.graphisme(gameRendu);

            for (const auto& tour : tours)
            {
                tour->render(gameRendu, myMap.getTailleCase());
            }

            for (const auto& ennemi : ennemis)
            {
                ennemi->render(gameRendu);
            }

            for (const auto& projectile : projectiles)
            {
                projectile.render(gameRendu);
            }

            SDL_Rect curseurRect = {
                curseurX * myMap.getTailleCase(),
                curseurY * myMap.getTailleCase(),
                myMap.getTailleCase(),
                myMap.getTailleCase()
            };

            gameRendu.setColor(255, 255, 255, 255);
            SDL_RenderDrawRect(gameRendu.getNativeRenderer(), &curseurRect);

            gameRendu.present();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erreur fatale : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}