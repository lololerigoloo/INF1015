#pragma once
#include "Piece.hpp"
#include "Echiquier.hpp"
namespace Modele
{
    class Pion : public Piece
    {
    public:
        Pion(Position position, Couleur couleur) : Piece(position, couleur) {}

        char symbole() const override { return 'P'; }
        std::vector<Position> calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>>& echiquier) override;
        QString nomImage() const override {
            return (couleur_ == Couleur::Blanc) ? "pionBlanc" : "pionNoir";
        }
    };
}