#include "tour.hpp"

#include <cmath>

Tour::Tour(int gridX, int gridY, int degat, float portee, float delaiAttaque)
    : gridX_(gridX),
      gridY_(gridY),
      degat_(degat),
      portee_(portee),
      delaiAttaque_(delaiAttaque),
      timerAttaque_(0.0f)
{
}

void Tour::update(
    float dt,
    std::vector<std::unique_ptr<Ennemi>>& ennemis,
    std::vector<Projectile>& projectiles,
    int tailleCase
)
{
    if (timerAttaque_ > 0.0f)
    {
        timerAttaque_ -= dt;
    }

    if (timerAttaque_ > 0.0f)
    {
        return;
    }

    Ennemi* cible = trouverCible(ennemis, tailleCase);

    if (cible != nullptr)
    {
        creerProjectileVers(*cible, projectiles, tailleCase);
        attaquer(*cible);

        timerAttaque_ = delaiAttaque_;
    }
}

void Tour::attaquer(Ennemi& ennemi)
{
    ennemi.prendreDegat(degat_);
}

bool Tour::peutCibler(const Ennemi& ennemi) const
{
    (void)ennemi;
    return true;
}

bool Tour::estDansPortee(const Ennemi& ennemi, int tailleCase) const
{
    float centreTourX = gridX_ * tailleCase + tailleCase / 2.0f;
    float centreTourY = gridY_ * tailleCase + tailleCase / 2.0f;

    float dx = ennemi.getX() - centreTourX;
    float dy = ennemi.getY() - centreTourY;

    float distance = std::sqrt(dx * dx + dy * dy);

    return distance <= portee_;
}

Ennemi* Tour::trouverCible(
    std::vector<std::unique_ptr<Ennemi>>& ennemis,
    int tailleCase
)
{
    Ennemi* meilleureCible = nullptr;
    float meilleureProgression = -1.0f;

    for (auto& ennemi : ennemis)
    {
        if (!ennemi)
        {
            continue;
        }

        if (ennemi->estMort())
        {
            continue;
        }

        if (ennemi->estArrive())
        {
            continue;
        }

        if (!peutCibler(*ennemi))
        {
            continue;
        }

        if (!estDansPortee(*ennemi, tailleCase))
        {
            continue;
        }

        float progression = ennemi->getProgressionChemin();

        if (progression > meilleureProgression)
        {
            meilleureProgression = progression;
            meilleureCible = ennemi.get();
        }
    }

    return meilleureCible;
}

void Tour::creerProjectileVers(
    const Ennemi& ennemi,
    std::vector<Projectile>& projectiles,
    int tailleCase
) const
{
    float centreTourX = gridX_ * tailleCase + tailleCase / 2.0f;
    float centreTourY = gridY_ * tailleCase + tailleCase / 2.0f;

    projectiles.emplace_back(
        centreTourX,
        centreTourY,
        ennemi.getX(),
        ennemi.getY()
    );
}

int Tour::getGridX() const
{
    return gridX_;
}

int Tour::getGridY() const
{
    return gridY_;
}