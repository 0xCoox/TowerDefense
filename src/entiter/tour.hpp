#include "entite.hpp"

class Tour : public Entite {
public:
    Tour(float x, float y, int pv, float cadenceTir, float porte);
    //overirde important pour eviter les fautes 
    void update(float dt) override; 
    void render(Rendu& rendu) const override;

protected: 
    int m_pv;
    float m_cadenceT;
    float m_porte;    
    float m_cooldown;   
};