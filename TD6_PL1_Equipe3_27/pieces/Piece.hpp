// ============================================================
// Piece.hpp — Classe de base abstraite pour toutes les pièces
// Namespace : Modele
// ============================================================
#pragma once
#include "../Position.hpp"
#include "../exception.hpp"
#include <memory>
#include <vector>
#include <QString>

namespace Modele
{
    enum class Couleur { Blanc, Noir };

    class Piece {
    public:
        Piece(Position position, Couleur couleur) : position_(position), couleur_(couleur) {}
        virtual ~Piece() = default;
        virtual char symbole() const = 0;
        virtual std::vector<Position> calculerDeplacementsPossibles(
            const std::vector<std::vector<std::shared_ptr<Piece>>>& echiquier) = 0;
        virtual QString nomImage() const = 0;
        virtual void setPosition(Position pos) { position_ = pos; }
        Position position() const { return position_; }
        Couleur couleur() const { return couleur_; }

    protected:
        Position position_;
        Couleur couleur_;
        std::vector<Position> deplacementsPossibles_;
    };
}