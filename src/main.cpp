#include "core/window.hpp"
#include "carte/carte.hpp"
#include "core/rendu.hpp"
#include "core/input_manager.hpp"
#include "entiter/ennemi.hpp"
#include "waves/wave_manager.hpp"

#include <iostream>
#include <chrono>
#include <vector>
#include <memory>
#include <algorithm>

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
        WaveManager waveManager;

        int numeroVague = 1;
        int viesJoueur = 20;

        auto referential_time = std::chrono::steady_clock::now();

        while (isRunning)
        {
            auto timeGoingOn = std::chrono::steady_clock::now();

            std::chrono::duration<float> tempsreel = timeGoingOn - referential_time;
            float dt = tempsreel.count();

            referential_time = timeGoingOn;

            input.update();

            if (input.shouldQuit() || input.isKeyPressed(SDLK_ESCAPE))
            {
                isRunning = false;
            }

            if (input.isKeyPressed(SDLK_SPACE))
            {
                isPaused = !isPaused;
            }

            if (input.isKeyPressed(SDLK_RETURN))
            {
                waveManager.lancerVague(numeroVague);
                numeroVague++;
            }

            if (!isPaused)
            {
                waveManager.update(dt, ennemis, myMap.getChemin());

                for (auto& ennemi : ennemis)
                {
                    ennemi->update(dt, myMap.getChemin());
                }

                int ennemisArrives = 0;

                for (const auto& ennemi : ennemis)
                {
                    if (ennemi->estArrive())
                    {
                        ennemisArrives++;
                    }
                }

                viesJoueur -= ennemisArrives;

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

            for (const auto& ennemi : ennemis)
            {
                ennemi->render(gameRendu);
            }

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