#include "jeu/jeu.hpp"

#include <exception>
#include <iostream>

int main()
{
    try
    {
        Jeu jeu;
        jeu.lancer();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erreur fatale : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}