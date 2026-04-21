#include "entite.hpp" 
class Ennemi : public Entite {
public:

    Ennemi(float x, float y, float vitesse, int pv);

    void update(float dt);
    void render(Rendu& rendu) const;

private:
    float m_vitesse;
    int m_pv;
};