#pragma once
#include <memory>
#include "Piece.hpp"
#include "Position.hpp"
#include <vector>
namespace Modele 
{
    class Echiquier {
    public:
        Echiquier();
        ~Echiquier();
        void ajouterPiece(std::shared_ptr<Piece> piece);
        std::shared_ptr<Piece> getPiece(const Position& position) const;
        static bool estPositionValide(const Position& position) {
            return position.x() >= 0 && position.x() < N_CASES && position.y() >= 0 && position.y() < N_CASES;
        }
        static const int N_CASES = 8;
    private:
        std::vector<std::vector<std::shared_ptr<Piece>>> cases_ = std::vector<std::vector<std::shared_ptr<Piece>>>(N_CASES, std::vector<std::shared_ptr<Piece>>(N_CASES, nullptr)); 
    };
    
}