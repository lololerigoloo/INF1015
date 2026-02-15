#include "Jeu.hpp"
#include <iostream>
using namespace std;


ostream& operator<<(ostream &os, const Jeu &jeu)
{
    os << "Titre: " << jeu.titre_ << "\n"
       << "Année de sortie: " << jeu.anneeSortie_ << "\n"
       << "Développeur: " << jeu.developpeur_ << "\n"
       << "Concepteurs:\n";

    for (int i = 0; i < jeu.listeConcepteurs_.taille(); i++)
    {
        const Concepteur &c = jeu.listeConcepteurs_[i];
        os << "  - " << c.getNom() 
           << " (Né en " << c.getAnneeNaissance() 
           << ", " << c.getPays() << ")\n";
    }

    return os;
}

std::shared_ptr<Concepteur> Jeu::trouverConcepteur(
    const std::function<bool(const Concepteur&)>& critere) const
{
    return listeConcepteurs_.trouver(critere);
}


