// ============================================================
// Cavalier.hpp — Pièce Cavalier (mouvement en L)
// Namespace : Modele
// ============================================================
#pragma once
#include "Piece.hpp"

namespace Modele
{
    class Cavalier : public Piece
    {
    public:
        Cavalier(Position position, Couleur couleur);
        ~Cavalier();
        char symbole() const override { return 'C'; }
        std::vector<Position> calculerDeplacementsPossibles(
            const std::vector<std::vector<std::shared_ptr<Piece>>>& echiquier) override;
        QString nomImage() const override;

    private:
        static int nbCavaliersBlancs_;
        static int nbCavaliersNoirs_;
    };
}