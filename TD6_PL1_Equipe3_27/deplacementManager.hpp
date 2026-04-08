#pragma once
#include "Echiquier.hpp"
namespace Modele
{
    class DeplacementManager
    {
        
    public:
        DeplacementManager(std::shared_ptr<Echiquier> echiquier) : echiquier_(echiquier) {}
        ~DeplacementManager();
        void deplacer(const Position& depart, const Position& fin);
        void setPiecesSelectionnee(std::shared_ptr<Piece> piece) { piecesSelectionnee_ = piece; }
        bool estEchecApresDeplacement(const Position& depart, const Position& fin);
        std::shared_ptr<Piece> getPiecesSelectionnee() const { return piecesSelectionnee_; }
    private:
        std::shared_ptr<Echiquier> echiquier_;
        std::shared_ptr<Piece> piecesSelectionnee_ = nullptr;
        Couleur tour_ = Couleur::Blanc;
    };
}