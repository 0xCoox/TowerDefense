#include "joueur.hpp"

Joueur::Joueur(int argentInitial, int viesInitiales)
    : argent_(argentInitial),
      vies_(viesInitiales)
{
}

int Joueur::getArgent() const
{
    return argent_;
}

int Joueur::getVies() const
{
    return vies_;
}

bool Joueur::peutPayer(int cout) const
{
    return argent_ >= cout;
}

bool Joueur::payer(int cout)
{
    if (!peutPayer(cout))
    {
        return false;
    }

    argent_ -= cout;
    return true;
}

void Joueur::ajouterArgent(int montant)
{
    if (montant > 0)
    {
        argent_ += montant;
    }
}

void Joueur::perdreVie(int nombre)
{
    if (nombre <= 0)
    {
        return;
    }

    vies_ -= nombre;

    if (vies_ < 0)
    {
        vies_ = 0;
    }
}

bool Joueur::estMort() const
{
    return vies_ <= 0;
}