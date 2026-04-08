#pragma once
#include "Position.hpp"
#include "Echiquier.hpp"
#include <vector>
#include "Piece.hpp"
namespace Modele
{
    class Roi : public Piece
    {
    private:
        bool aBouge_ = false; // pour le roque
        std::vector<Position> deplacementsPossibles_;

    public:
        Roi(Position position, Couleur couleur) : Piece(position, couleur) {}
        ~Roi();
        char symbole() const override { return 'R'; }
        std::vector<Position> calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>> &echiquier) override;
        QString nomImage() const override
        {
            return (couleur_ == Couleur::Blanc) ? "roiBlanc" : "roiNoir";
        }
    };

}
