#include "ListeDeveloppeurs.hpp"
#include <iostream>
#include "Developpeur.hpp"
using namespace std;
ListeDeveloppeurs::ListeDeveloppeurs()
{
    nElements = 0;
    capacite = 2;
    elements = new Developpeur*[capacite];
}

ListeDeveloppeurs::~ListeDeveloppeurs()
{
    delete[] elements;
}
void ListeDeveloppeurs::afficher() const
{
    for (unsigned i = 0; i < nElements; ++i)
    {
        (elements[i])->AfficherInfosJeux();
    }
}
void ListeDeveloppeurs::ajouterDeveloppeur(Developpeur* dev)
{
    // Vérifier s'il existe déjà
    for (unsigned i = 0; i < nElements; ++i)
    {
        if (elements[i] == dev)
            return;
    }

    if (nElements >= capacite)
    {
        unsigned nouvelleCapacite = capacite * 2;
        Developpeur** nouveaux = new Developpeur*[nouvelleCapacite];

        for (unsigned i = 0; i < nElements; ++i)
            nouveaux[i] = elements[i];

        delete[] elements;
        elements = nouveaux;
        capacite = nouvelleCapacite;
    }

    elements[nElements++] = dev;
}

void ListeDeveloppeurs::retirerDeveloppeur(Developpeur* developpeurAEnlever)
{
    unsigned index = nElements;

    for (unsigned i = 0; i < nElements; ++i)
    {
        if (elements[i] == developpeurAEnlever)
        {
            index = i;
            break;
        }
    }

    if (index == nElements)
        return;

    for (unsigned i = index; i < nElements - 1; ++i)
    {
        elements[i] = elements[i + 1];
    }

    nElements--;
    elements[nElements] = nullptr;
}
 