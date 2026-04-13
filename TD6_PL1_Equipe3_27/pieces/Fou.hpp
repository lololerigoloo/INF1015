#pragma once
#include "Piece.hpp"

namespace Modele
{ 
    class Fou : public Piece 
    {
    public:
        Fou(Position position, Couleur couleur);
        char symbole() const override { return 'F'; }
        std::vector<Position> calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>>& echiquier) override;
        QString nomImage() const override {
            return (couleur_ == Couleur::Blanc) ? "fouBlanc" : "fouNoir";
        }
        ~Fou();
        int getNbFousBlancs() const { return nbFousBlancs_; }
        int getNbFousNoirs() const { return nbFousNoirs_; }

    private:
        static int nbFousBlancs_;
        static int nbFousNoirs_;
    };
    
}
