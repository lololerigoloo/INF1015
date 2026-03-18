#pragma once
#include "Personnage.hpp"
#include "Vilain.hpp"
#include <vector>

class Hero : virtual public Personnage
{
public:
    Hero(const std::string &nom, const std::string &parution, std::vector<std::string> allies, Vilain *ennemies)
        : Personnage(nom, parution),
          allies_(allies),
          ennemies_(ennemies)
    {
    }
    void afficher(std::ostream &os) const override
    {
        Personnage::afficher(os);
        os << Personnage::getCouleur() << "Ennemi : ";
        if (ennemies_ != nullptr)
            os << ennemies_->getNom();
        os << "\033[0m" << std::endl;
        os << Personnage::getCouleur() << "Allies :" << "\033[0m" << std::endl;
        for (auto &a : allies_)
            os << Personnage::getCouleur() << a << "\033[0m" << std::endl;
    }

    // void changerCouleur(int palette) override
    // {
    //     Personnage::changerCouleur(palette);
    // }
    friend std::ostream& operator<<(std::ostream &os, const Hero &hero);
    const std::vector<std::string> &getAllies() const
    {
        return allies_;
    }

    Vilain *getEnnemies() const
    {
        return ennemies_;
    }
    void setAllies(const std::vector<std::string> &allies)
    {
        allies_ = allies;
    }

private:
    std::vector<std::string> allies_;
    Vilain *ennemies_;

protected:
    Hero(const Hero &) = default;
    Hero &operator=(const Hero &) = default;
};
std::ostream& operator<<(std::ostream &os, const Hero &hero)
{
    hero.afficher(os);
    return os;
}