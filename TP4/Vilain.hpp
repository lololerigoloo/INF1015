#pragma once
#include "Personnage.hpp"

class Vilain : public virtual Personnage
{
public:
    Vilain(const std::string& nom, const std::string& parution , const std::string& objectif)
    : Personnage(nom, parution),
      objectif_(objectif)
    {}
    void afficher(std::ostream& os) const override
    {
        Personnage::afficher(os);
        os << Personnage::getCouleur() << "Objectif : " << objectif_  << "\033[0m" << std::endl;
    }
    void changerCouleur(int palette) override
    {
        Personnage::changerCouleur(palette);
    }

    const std::string& getObjectif() const
    {
        return objectif_;
    }
    friend std::ostream& operator<<(std::ostream& os, const Vilain& vilain);
private:
    std::string objectif_;
protected:
    Vilain(const Vilain&) = default;
    Vilain& operator=(const Vilain&) = default;
};
std::ostream& operator<<(std::ostream& os, const Vilain& vilain)
{
    vilain.afficher(os);
    return os;
}