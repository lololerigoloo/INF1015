#pragma once
#include <ostream>
#include <string>
class Affichable
{
public:
    virtual void afficher(std::ostream &os) const = 0;
    virtual ~Affichable() = default; // Destructeur virtuel par défaut
    virtual void changerCouleur(int couleur) = 0;
};