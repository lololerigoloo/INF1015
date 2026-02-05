#pragma once
#include "Developpeur.hpp"

class ListeDeveloppeurs
{
public:
    ListeDeveloppeurs();
    ~ListeDeveloppeurs();

    void afficher() const;
    void ajouterDeveloppeur(Developpeur*);
    void retirerDeveloppeur(Developpeur*);

private:
    unsigned nElements;
    unsigned capacite;
    Developpeur** elements;
};

