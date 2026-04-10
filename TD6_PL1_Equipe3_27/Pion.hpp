#pragma once
#include "Piece.hpp"
#include "Echiquier.hpp"
namespace Modele
{
    class Pion : public Piece
    {
    public:
        Pion(Position position, Couleur couleur);
        ~Pion() {
            if (couleur_ == Couleur::Blanc)
                nbPionsBlancs_--;
            else
                nbPionsNoirs_--;
        }
        char symbole() const override { return 'P'; }
        std::vector<Position> calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>> &echiquier) override;
        QString nomImage() const override
        {
            return (couleur_ == Couleur::Blanc) ? "pionBlanc" : "pionNoir";
        }
        static int NbPionsBlancs() { return nbPionsBlancs_; }
        static int NbPionsNoirs() { return nbPionsNoirs_; }

    private:
        static int nbPionsBlancs_;
        static int nbPionsNoirs_;
    };

}