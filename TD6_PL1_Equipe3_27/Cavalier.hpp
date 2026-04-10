#pragma once
#include "Piece.hpp"
#include "exception.hpp"
#include "Position.hpp"
#include <vector>
#include "Echiquier.hpp"

namespace Modele
{
    class Cavalier : public Piece
    {
    public:
        Cavalier(Position position, Couleur couleur) : Piece(position, couleur)
        {
            if (couleur == Couleur::Blanc)
            {
                nbCavaliersBlancs_++;
                if (nbCavaliersBlancs_ > 2)
                {
                    nbCavaliersBlancs_--;
                    throw ExceptionCavalierBlancs();
                }
                else
                {
                    nbCavaliersNoirs_++;
                    if (nbCavaliersNoirs_ > 2)
                    {
                        nbCavaliersNoirs_--;
                        throw ExceptionCavalierNoirs();
                    }
                }
            }
        }
        ~Cavalier()
        {
            if (couleur_ == Couleur::Blanc)
                nbCavaliersBlancs_--;
            else
                nbCavaliersNoirs_--;
        }
        char symbole() const override { return 'C'; }
        std::vector<Position> calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>>& echiquier) override;
        QString nomImage() const override;
    private:
        static int nbCavaliersBlancs_;
        static int nbCavaliersNoirs_;
    };
}
