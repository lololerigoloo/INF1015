#pragma once
#include "Piece.hpp"
#include "Echequier.hpp"
namespace Modele
{
    class Pion : public Piece
    {
    public:
        Pion(Position position, Couleur couleur) : Piece(position, couleur) {}

        char symbole() const override { return 'P'; }
        void calculerDeplacementsPossibles(const std::vector<std::vector<Piece*>>& echiquier) override;
    };

    void Pion::calculerDeplacementsPossibles(const std::vector<std::vector<Piece*>>& echiquier) {
        deplacementsPossibles_.clear();
        int direction = (couleur_ == Couleur::Blanc) ? -1 : 1; // les blancs vont vers le haut, les noirs vers le bas
        int x = position_.x();
        int y = position_.y();

        // déplacement de base : une case devant
        if (x + direction >= 0 && x + direction < Echiquier::N_CASES && echiquier[x + direction][y] == nullptr) {
            deplacementsPossibles_.emplace_back(x + direction, y);
            // si c'est la première fois que le pion bouge, il peut avancer de deux cases
            if ((couleur_ == Couleur::Blanc && x == 6) || (couleur_ == Couleur::Noir && x == 1)) {
                if (echiquier[x + 2 * direction][y] == nullptr) {
                    deplacementsPossibles_.emplace_back(x + 2 * direction, y);
                }
            }
        }

        // captures possibles : diagonales
        for (int dy : {-1, 1}) {
            if (y + dy >= 0 && y + dy < Echiquier::N_CASES && x + direction >= 0 && x + direction < Echiquier::N_CASES) {
                Piece* pieceAdverse = echiquier[x + direction][y + dy];
                if (pieceAdverse != nullptr && pieceAdverse->couleur() != couleur_) {
                    deplacementsPossibles_.emplace_back(x + direction, y + dy);
                }
            }
        }
    }
}