#pragma once

class Joueur
{
private:
    int argent_;
    int vies_;

public:
    Joueur(int argentInitial, int viesInitiales);

    int getArgent() const;
    int getVies() const;

    bool peutPayer(int cout) const;
    bool payer(int cout);

    void ajouterArgent(int montant);
    void perdreVie(int nombre);

    bool estMort() const;
};