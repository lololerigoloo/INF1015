#pragma once
#include "Heros.hpp"
#include "Vilain.hpp"

class VilainHero : public Hero, public Vilain
{
public:
    VilainHero(const Vilain &vilain, const Hero &hero)
        : Personnage(
              vilain.getNom() + "-" + hero.getNom(),
              vilain.getParution() + "-" + hero.getParution()),
          Hero(hero),
          Vilain(vilain),
          nomFusion_(vilain.getNom() + "-" + hero.getNom()),
          parutionFusion_(vilain.getParution() + "-" + hero.getParution()),
          missionSpeciale_(
              vilain.getObjectif() +
              " dans le monde de " +
              hero.getParution())
    {
    }

    void afficher(std::ostream &os) const override
    {
        os << Personnage::getCouleur() << "Nom : " << nomFusion_ << "\033[0m" << std::endl;

        os << Personnage::getCouleur() << "Parution : "
           << parutionFusion_
           << "\033[0m" << std::endl;

        os << Personnage::getCouleur() << "Objectif : "
           << getObjectif()
           << "\033[0m" << std::endl;

        os << Personnage::getCouleur() << "Ennemi : "
           << getEnnemies()->getNom()
           << "\033[0m" << std::endl;

        os << Personnage::getCouleur() << "Allies :" << "\033[0m" << std::endl;

        for (std::string a : getAllies())
            os << Personnage::getCouleur() << "        " << a << "\033[0m" << std::endl;

        os << Personnage::getCouleur() << "Mission speciale : "
           << missionSpeciale_
           << "\033[0m" << std::endl;
    }
    friend std::ostream &operator<<(std::ostream &os, const VilainHero &vilainHero);

    void changerCouleur(int palette) override
    {
        Hero::changerCouleur(palette);
        Vilain::changerCouleur(palette);
    }

private:
    std::string nomFusion_;
    std::string parutionFusion_;

    std::string missionSpeciale_;

protected:
    VilainHero(const VilainHero &) = default;
    VilainHero &operator=(const VilainHero &) = default;
};
std::ostream &operator<<(std::ostream &os, const VilainHero &vilainHero)
{
    vilainHero.afficher(os);
    return os;
}