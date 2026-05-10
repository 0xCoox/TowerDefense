#include "game_interaction_handler.hpp"

#include "game_config.hpp"

#include <iostream>
#include <optional>

namespace
{
    const char* nomTypeTour(TypeTour typeTour)
    {
        switch (typeTour)
        {
            case TypeTour::Basique:
                return "Tour basique";

            case TypeTour::Sniper:
                return "Tour sniper";

            case TypeTour::Canon:
                return "Tour canon";

            case TypeTour::Glace:
                return "Tour glace";

            case TypeTour::AntiAir:
                return "Tour anti-air";
        }

        return "Tour inconnue";
    }
}

GameInteractionHandler::GameInteractionHandler(
    TypeTour typeTourParDefaut,
    int curseurXInitial,
    int curseurYInitial
)
    : inputHandler_(),
      curseurX_(curseurXInitial),
      curseurY_(curseurYInitial),
      typeTourSelectionne_(typeTourParDefaut),
      afficherPorteePlacement_(false),
      tourSelectionneeIndex_(-1),
      selectionVerrouillee_(false),
      dragTourActif_(false),
      dragTourType_(typeTourParDefaut),
      dragTourCout_(0),
      sourisGaucheAvant_(false)
{
}

void GameInteractionHandler::traiterEntrees(
    InputManager& input,
    BouttonManager& guiManager,
    Hud& hud,
    GameWorld& world,
    TextureManager& textureManager,
    bool& estLance,
    bool& estPause
)
{
    inputHandler_.traiterEntrees(
        input,
        guiManager,
        estLance,
        estPause,
        curseurX_,
        curseurY_,
        [this](TypeTour typeTour)
        {
            selectionnerTour(typeTour);
        },
        [this, &world, &textureManager]()
        {
            essayerAjouterTour(world, textureManager);
        },
        [&world]()
        {
            world.lancerVague();
        }
    );

    int sourisX = input.getMouseX();
    int sourisY = input.getMouseY();

    bool deplacementClavier =
        input.isKeyPressed(InputManager::Key::Up) ||
        input.isKeyPressed(InputManager::Key::Down) ||
        input.isKeyPressed(InputManager::Key::Left) ||
        input.isKeyPressed(InputManager::Key::Right);

    if (sourisDansMap(sourisX, sourisY))
    {
        if (!selectionVerrouillee_ && !deplacementClavier)
        {
            curseurX_ = getGridXDepuisSouris(world, sourisX);
            curseurY_ = getGridYDepuisSouris(world, sourisY);
        }
    }

    bool sourisGauche =
        input.isMouseButtonDown(InputManager::MouseButton::Left);

    bool sourisCliquee =
        input.isMouseButtonPressed(InputManager::MouseButton::Left);

    if (sourisCliquee && !dragTourActif_)
    {
        gererClicSouris(
            hud,
            world,
            textureManager,
            sourisX,
            sourisY
        );
    }

    if (dragTourActif_ && !sourisGauche && sourisGaucheAvant_)
    {
        terminerDragTour(
            world,
            textureManager,
            sourisX,
            sourisY
        );
    }

    if (dragTourActif_)
    {
        typeTourSelectionne_ = dragTourType_;
        afficherPorteePlacement_ = true;
    }

    sourisGaucheAvant_ = sourisGauche;
}

void GameInteractionHandler::selectionnerTour(TypeTour typeTour)
{
    typeTourSelectionne_ = typeTour;
    afficherPorteePlacement_ = true;

    std::cout << "Selection : "
              << nomTypeTour(typeTour)
              << std::endl;
}

void GameInteractionHandler::essayerAjouterTour(
    GameWorld& world,
    TextureManager& textureManager
)
{
    if (world.placerTour(
            typeTourSelectionne_,
            curseurX_,
            curseurY_,
            textureManager
        ))
    {
        afficherPorteePlacement_ = false;
    }
}

void GameInteractionHandler::gererClicSouris(
    Hud& hud,
    GameWorld& world,
    TextureManager& textureManager,
    int sourisX,
    int sourisY
)
{
    std::optional<TypeTour> paletteType =
        hud.getPaletteTypeAt(sourisX, sourisY);

    if (paletteType.has_value())
    {
        selectionVerrouillee_ = false;

        std::optional<int> cout =
            world.preparerAchatTour(
                paletteType.value(),
                textureManager
            );

        if (cout.has_value())
        {
            dragTourActif_ = true;
            dragTourType_ = paletteType.value();
            dragTourCout_ = cout.value();
            typeTourSelectionne_ = paletteType.value();
            afficherPorteePlacement_ = true;
        }

        return;
    }

    if (!sourisDansMap(sourisX, sourisY))
    {
        return;
    }

    int gridX = getGridXDepuisSouris(world, sourisX);
    int gridY = getGridYDepuisSouris(world, sourisY);

    int indexClique = world.trouverIndexTour(gridX, gridY);

    if (indexClique != -1)
    {
        if (selectionVerrouillee_ &&
            tourSelectionneeIndex_ == indexClique)
        {
            selectionVerrouillee_ = false;
        }
        else
        {
            selectionVerrouillee_ = true;
        }

        tourSelectionneeIndex_ = indexClique;
        curseurX_ = gridX;
        curseurY_ = gridY;
    }
    else
    {
        tourSelectionneeIndex_ = -1;
        selectionVerrouillee_ = false;
        afficherPorteePlacement_ = false;
    }
}

void GameInteractionHandler::terminerDragTour(
    GameWorld& world,
    TextureManager& textureManager,
    int sourisX,
    int sourisY
)
{
    bool placee = false;

    if (sourisDansMap(sourisX, sourisY))
    {
        int gridX = getGridXDepuisSouris(world, sourisX);
        int gridY = getGridYDepuisSouris(world, sourisY);

        placee = world.placerTourDejaPayee(
            dragTourType_,
            gridX,
            gridY,
            textureManager
        );
    }

    if (!placee)
    {
        world.joueur().ajouterArgent(dragTourCout_);
    }

    dragTourActif_ = false;
    dragTourCout_ = 0;
    afficherPorteePlacement_ = false;
}

void GameInteractionHandler::ameliorerTourSelectionnee(GameWorld& world)
{
    int gridX = curseurX_;
    int gridY = curseurY_;

    getCoordonneesTourSelectionnee(
        world,
        gridX,
        gridY
    );

    world.ameliorerTour(gridX, gridY);
}

void GameInteractionHandler::vendreTourSelectionnee(GameWorld& world)
{
    int gridX = curseurX_;
    int gridY = curseurY_;

    getCoordonneesTourSelectionnee(
        world,
        gridX,
        gridY
    );

    if (world.vendreTour(gridX, gridY))
    {
        tourSelectionneeIndex_ = -1;
        selectionVerrouillee_ = false;
    }
}

bool GameInteractionHandler::sourisDansMap(
    int sourisX,
    int sourisY
) const
{
    return sourisX >= 0 &&
           sourisX < GameConfig::LARGEUR_MAP &&
           sourisY >= 0 &&
           sourisY < GameConfig::HAUTEUR_FENETRE;
}

int GameInteractionHandler::getGridXDepuisSouris(
    const GameWorld& world,
    int sourisX
) const
{
    return sourisX / world.carte().getTailleCase();
}

int GameInteractionHandler::getGridYDepuisSouris(
    const GameWorld& world,
    int sourisY
) const
{
    return sourisY / world.carte().getTailleCase();
}

void GameInteractionHandler::getCoordonneesTourSelectionnee(
    const GameWorld& world,
    int& gridX,
    int& gridY
) const
{
    if (tourSelectionneeIndex_ != -1 &&
        tourSelectionneeIndex_ < static_cast<int>(world.tours().size()))
    {
        gridX = world.tours()[tourSelectionneeIndex_]->getGridX();
        gridY = world.tours()[tourSelectionneeIndex_]->getGridY();
    }
}