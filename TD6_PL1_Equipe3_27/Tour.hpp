#pragma once
#include "Piece.hpp"
#include "Position.hpp"
#include <vector>
#include "Echiquier.hpp"
namespace Modele
{

    class Tour : public Piece
    {
    public:
        Tour(Position position, Couleur couleur) : Piece(position, couleur) {}

        char symbole() const override { return 'T'; }
        std::vector<Position> calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>> &echiquier) override;
        QString nomImage() const override;
        bool aBouge() const { return aBouge_; }
        void setABouge(bool aBouge) { aBouge_ = aBouge; }

    private:
        bool aBouge_ = false;
    };

}