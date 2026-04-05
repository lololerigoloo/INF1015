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
        void calculerDeplacementsPossibles(const std::vector<std::vector<Piece*>>& echiquier) override;

    };
    void Fou::calculerDeplacementsPossibles(const std::vector<std::vector<Piece*>>& echiquier) {
        deplacementsPossibles_.clear();
        int x = position_.x();
        int y = position_.y();

        // directions diagonales : (dx, dy)
        std::vector<std::pair<int, int>> directions = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        for (const auto& [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            while (nx >= 0 && nx < Echiquier::N_CASES && ny >= 0 && ny < Echiquier::N_CASES) {
                if (echiquier[nx][ny] == nullptr) {
                    deplacementsPossibles_.emplace_back(nx, ny);
                } else {
                    if (echiquier[nx][ny]->couleur() != couleur_) {
                        deplacementsPossibles_.emplace_back(nx, ny); // capture possible
                    }
                    break; // on arrête de regarder dans cette direction après la première pièce rencontrée
                }
                nx += dx;
                ny += dy;
            }
        }
    }
}