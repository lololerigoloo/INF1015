#pragma once
#include "Affichable.hpp"
#include <string>

class Personnage : public Affichable
{
public:
    Personnage(const std::string &nom, const std::string &parution)
        : couleur_("\033[0m"),
          _nom(nom),
          _parution(parution)
    {
    }

    void afficher(std::ostream &os) const override
    {
        os << couleur_
           << "Nom : " << _nom << std::endl
           << "Premiere apparition : " << _parution
           << "\033[0m" << std::endl;
    }

    void changerCouleur(int palette) override
    {
        switch (palette)
        {
        case 31:
            couleur_ = "\033[31m";
            break;
        case 32:
            couleur_ = "\033[32m";
            break;
        case 33:
            couleur_ = "\033[33m";
            break;
        case 34:
            couleur_ = "\033[34m";
            break;
        case 91:
            couleur_ = "\033[91m";
            break;
        case 92:
            couleur_ = "\033[92m";
            break;
        case 94:
            couleur_ = "\033[94m";
            break;
        case 95:
            couleur_ = "\033[95m";
            break;
        default:
            couleur_ = "\033[0m";
            break;
        }
    }
    friend std::ostream &operator<<(std::ostream &os, const Personnage& perso);
    const std::string &getNom() const
    {
        return _nom;
    }

    const std::string &getParution() const
    {
        return _parution;
    }
    const std::string &getCouleur() const
    {
        return couleur_;
    }

protected:
    Personnage(const Personnage &) = default;
    Personnage &operator=(const Personnage &) = default;

private:
    std::string couleur_;
    std::string _nom;
    std::string _parution;
};
std::ostream &operator<<(std::ostream &os, const Personnage &perso)
{
    os << perso.couleur_
       << "Nom : " << perso._nom << std::endl
       << "Premiere apparition : " << perso._parution
       << "\033[0m" << std::endl;
    return os;
}