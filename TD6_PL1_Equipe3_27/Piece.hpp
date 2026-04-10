#pragma once
#include "Position.hpp"
#include <vector>   
#include <QString>
#include "exception.hpp"
namespace Modele 
{
    enum class Couleur { Blanc, Noir };
    class Piece {
    public:
        Piece(Position position, Couleur couleur) : position_(position), couleur_(couleur) {} 
        virtual ~Piece() = default;
        virtual char symbole() const = 0; // retourne un caractère représentant la pièce
        virtual std::vector<Position> calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>>& echiquier) = 0;
        virtual QString nomImage() const = 0; // retourne le nom de l'image pour cette pièce (ex: "pionBlanc", "roiNoir")
        virtual void setPosition(Position pos) { position_ = pos; }
        Position position() const { return position_; }
        Couleur couleur() const { return couleur_; }
    protected:
        Position position_;
        Couleur couleur_;
        std::vector<Position> deplacementsPossibles_; // positions vers lesquelles la pièce peut se déplacer
    };
}