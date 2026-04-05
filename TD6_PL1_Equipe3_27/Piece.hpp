#pragma once
#include "Position.hpp"
#include <vector>   
namespace Modele 
{
    enum class Couleur { Blanc, Noir };
    class Piece {
    public:
        Piece(Position position, Couleur couleur) : position_(position), couleur_(couleur) {} 
        virtual ~Piece() = default;
        virtual char symbole() const = 0; // retourne un caractère représentant la pièce
        virtual void calculerDeplacementsPossibles(const std::vector<std::vector<Piece*>>& echiquier) = 0;
        Position position() const { return position_; }
        Couleur couleur() const { return couleur_; }
    protected:
        Position position_;
        Couleur couleur_;
        std::vector<Position> deplacementsPossibles_; // positions vers lesquelles la pièce peut se déplacer
    };
}