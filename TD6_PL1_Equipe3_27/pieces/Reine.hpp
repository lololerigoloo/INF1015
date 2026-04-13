#pragma once
#include "Piece.hpp"

namespace Modele {
    class Reine : public Piece {
    public:
        Reine(Position position, Modele::Couleur couleur);
        ~Reine();
        char symbole() const override { return 'Q'; }
        std::vector<Position> calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>>& echiquier) override;
        QString nomImage() const override;

    private:
        static int nbReinesBlanches_;
        static int nbReinesNoires_;
    };
}