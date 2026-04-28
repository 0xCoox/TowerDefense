#include "tour.hpp"

#include <cmath>

Tour::Tour(
    int gridX,
    int gridY,
    int degat,
    float portee,
    float delaiAttaque,
    float vitesseProjectile,
    int cout
)
    : gridX_(gridX),
      gridY_(gridY),
      degat_(degat),
      portee_(portee),
      delaiAttaque_(delaiAttaque),
      timerAttaque_(0.0f),
      vitesseProjectile_(vitesseProjectile),
      cout_(cout)
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

    std::optional<std::size_t> indexCible = trouverIndexCible(ennemis, tailleCase);

    if (!indexCible.has_value())
    {
        return;
    }

    Ennemi& cible = *ennemis[indexCible.value()];

    creerProjectileVers(cible, projectiles, tailleCase);

    timerAttaque_ = delaiAttaque_;
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

std::optional<std::size_t> Tour::trouverIndexCible(
    const std::vector<std::unique_ptr<Ennemi>>& ennemis,
    int tailleCase
) const
{
    std::optional<std::size_t> meilleurIndex;
    float meilleureProgression = -1.0f;

    for (std::size_t i = 0; i < ennemis.size(); i++)
    {
        const std::unique_ptr<Ennemi>& ennemi = ennemis[i];

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
            meilleurIndex = i;
        }
    }

    return meilleurIndex;
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
        ennemi.getId(),
        degat_,
        vitesseProjectile_
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

int Tour::getCout() const
{
    return cout_;
}