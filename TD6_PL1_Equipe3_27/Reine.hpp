#pragma once
#include "Piece.hpp"
#include "exception.hpp"
#include "Position.hpp"
#include <vector>
#include "Echiquier.hpp"

namespace Modele {
    class Reine : public Piece {
    public:
        Reine(Position position, Modele::Couleur couleur) : Piece(position, couleur) {
            if (couleur == Modele::Couleur::Blanc) {
                if (nbReinesBlanches_ >= 1) {
                    throw ExceptionReineBlanche();
                }
                nbReinesBlanches_++;
            } else {
                if (nbReinesNoires_ >= 1) {
                    throw ExceptionReineNoire();
                }
                nbReinesNoires_++;
            }
        }
        ~Reine();
        char symbole() const override { return 'Q'; }
        std::vector<Position> calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>>& echiquier) override;
        QString nomImage() const override;

    private:
        static int nbReinesBlanches_;
        static int nbReinesNoires_;
    };
}