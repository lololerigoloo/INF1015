#pragma once
#include <memory>
#include "Position.hpp"
#include "Piece.hpp"
namespace Modele
{
    class Echiquier;
    class DeplacementManager
    {

    public:
        DeplacementManager(Echiquier* echiquier) : echiquier_(echiquier) {}
        ~DeplacementManager();
        void deplacer(const Position &depart, const Position &fin);
        void setPiecesSelectionnee(std::shared_ptr<Piece> piece) { piecesSelectionnee_ = piece; }
        bool estEchecApresDeplacement(const Position &depart, const Position &fin);
        std::shared_ptr<Piece> getPiecesSelectionnee() const { return piecesSelectionnee_; }

    private:
        Echiquier* echiquier_;
        std::shared_ptr<Piece> piecesSelectionnee_ = nullptr;
        Couleur tour_ = Couleur::Blanc;
    };
}