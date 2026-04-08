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
        Fou(Position position, Couleur couleur) : Piece(position, couleur) {}

        char symbole() const override { return 'F'; }
        std::vector<Position> calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>>& echiquier) override;
        QString nomImage() const override {
            return (couleur_ == Couleur::Blanc) ? "fouBlanc" : "fouNoir";
        }

    };
    
}
