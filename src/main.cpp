#include "core/window.hpp"
#include "carte/carte.hpp"
#include "core/rendu.hpp"
#include <iostream>
#include <chrono>

int main() {
    try {
        Window gameWindow("Tower Defense", 1920, 1080);
        Rendu gameRendu(gameWindow.getNativeWindow());
        Carte myMap("assets/map.txt"); //
        bool isRunning = true;
        auto referential_time = std::chrono::steady_clock::now();
        SDL_Event event;

        // LA BOUCLE DE JEU
        while (isRunning) {
            //time Manager
            auto TimeGoingOn = std::chrono::steady_clock::now();
            std::chrono::duration<float> tempsreel = referential_time - TimeGoingOn;
            float dt = tempsreel.count();
            referential_time = TimeGoingOn;
            // On prépare le prochain tour
            // gere les evenements
            
            while (SDL_PollEvent(&event)) {
                // Si l'utilisateur clique sur la croix de la fenêtre
                if (event.type == SDL_QUIT) {
                    isRunning = false;
                }
                // (Plus tard, on ajoutera les touches du clavier ici)
            }

            // 2. MISE À JOUR (Logique du jeu, déplacements, etc.)
            // (Vide pour l'instant)

            // 3. RENDU (Dessin à l'écran)
            // (Vide pour l'instant, on y mettra le Renderer)
            gameRendu.setColor(0, 0, 0, 255);
            gameRendu.clear();
            myMap.graphisme(gameRendu);
            gameRendu.present();
        }

    } catch (const std::exception& e) {
        std::cerr << "Erreur fatale : " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}