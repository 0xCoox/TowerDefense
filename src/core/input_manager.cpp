#include "input_manager.hpp"

void InputManager::update()
{
    // On vide les touches pressées à chaque frame
    // Comme ça, isKeyPressed() ne reste vrai qu'une seule frame
    m_pressedKeys.clear();

    SDL_Event event;

    // On lit tous les événements SDL de cette frame
    while (SDL_PollEvent(&event))
    {
        // Si l'utilisateur ferme la fenêtre
        if (event.type == SDL_QUIT)
        {
            m_shouldQuit = true;
        }

        // Si une touche vient d'être appuyée
        if (event.type == SDL_KEYDOWN)
        {
            // event.key.repeat == 0 permet d'éviter la répétition automatique
            // quand on garde une touche appuyée longtemps
            if (event.key.repeat == 0)
            {
                m_pressedKeys.insert(event.key.keysym.sym);
            }
        }
    }

    // On récupère l'état actuel du clavier
    // Cela sert pour isKeyDown()
    m_keyboardState = SDL_GetKeyboardState(nullptr);
}

bool InputManager::shouldQuit() const
{
    return m_shouldQuit;
}

bool InputManager::isKeyDown(SDL_Keycode key) const
{
    // On convertit la touche SDL en scancode
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key);

    // Si l'état du clavier n'existe pas encore, on retourne false
    if (m_keyboardState == nullptr)
    {
        return false;
    }

    // Si la touche est actuellement maintenue
    if (m_keyboardState[scancode])
    {
        return true;
    }

    // Sinon la touche n'est pas appuyée
    return false;
}

bool InputManager::isKeyPressed(SDL_Keycode key) const
{
    // On regarde si la touche est dans la liste des touches appuyées cette frame
    if (m_pressedKeys.find(key) != m_pressedKeys.end())
    {
        return true;
    }

    return false;
}