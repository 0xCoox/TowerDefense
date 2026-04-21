#include "entite.hpp" 
class projectile : public Entite {
public:

    projectile(float x, float y, float vitesse, int degat);

    void update(float dt) override;
    void render(Rendu& rendu) const override;

private:
    int m_degats;
    float m_vitesse;
};