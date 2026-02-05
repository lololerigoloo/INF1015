#include "Developpeur.hpp"
#include <string>
#include <iostream>
#include <utility>
#include "ListeJeux.hpp"
#include "Jeu.hpp"
using namespace std;

Developpeur::Developpeur(const pair<string, ListeJeux> &paireNomJeux)
{
    paireNomJeux_.first = paireNomJeux.first;
    paireNomJeux_.second.nElements = 0;
    paireNomJeux_.second.capacite = 0;
    paireNomJeux_.second.elements = nullptr;
}

Developpeur::~Developpeur()
{
    delete[] paireNomJeux_.second.elements;
    paireNomJeux_.second.elements = nullptr;
}

string Developpeur::Nom() const
{
    return paireNomJeux_.first;
}
unsigned Developpeur::NombreParticipationJeuxDansListe(const ListeJeux &liste)
{
    string nomDev = paireNomJeux_.first;
    unsigned count = 0;
    for (unsigned i = 0; i < liste.nElements; ++i)
    {
        if (liste.elements[i]->developpeur == nomDev)
        {
            count++;
        }
    }
    return count;
}

void Developpeur::MettreAJourListeJeux(const ListeJeux &nouvelleListe)
{
    delete[] paireNomJeux_.second.elements;
    paireNomJeux_.second.elements = nullptr;

    unsigned nbjeuxDev = NombreParticipationJeuxDansListe(nouvelleListe);
    if (nbjeuxDev > 0)
        paireNomJeux_.second.elements = new Jeu *[nbjeuxDev];
    else
        paireNomJeux_.second.elements = nullptr;

    paireNomJeux_.second.capacite = nbjeuxDev;
    paireNomJeux_.second.nElements = 0;

    string nomDev = paireNomJeux_.first;

    for (unsigned i = 0; i < nouvelleListe.nElements; ++i)
    {
        if (nouvelleListe.elements[i]->developpeur == nomDev)
        {
            paireNomJeux_.second.elements[paireNomJeux_.second.nElements++] =
                nouvelleListe.elements[i];
            continue;
        }
    }
}

void Developpeur::AfficherInfosJeux()
{
    cout << "Développeur: " << paireNomJeux_.first << endl;
    cout << "Jeux développés:" << endl;
    for (unsigned i = 0; i < paireNomJeux_.second.nElements; ++i)
    {
        Jeu *jeu = paireNomJeux_.second.elements[i];
        cout << "  - " << jeu->titre << " (" << jeu->anneeSortie << ")" << endl;
    }
}
