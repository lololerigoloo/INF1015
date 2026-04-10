#pragma once
#include "Piece.hpp"
#include "Position.hpp"
#include <vector>
#include "Echiquier.hpp"
namespace Modele
{ 
    class Fou : public Piece 
    {
    public:
        Fou(Position position, Couleur couleur) : Piece(position, couleur) 
        {
            if(couleur == Couleur::Blanc)
            {
                 nbFousBlancs_++;
                if(nbFousBlancs_ > 2)
                {
                    nbFousBlancs_--;
                    throw ExceptionNombreFousBlancs();
                }
            }
               
            else
            {

                nbFousNoirs_++;
                if(nbFousNoirs_ > 2)
                {
                    nbFousNoirs_--;
                    throw ExceptionNombreFousNoirs();
                }
            }
        }

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
