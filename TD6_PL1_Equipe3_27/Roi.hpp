#pragma once
#include "Position.hpp"
#include "Echiquier.hpp"
#include <vector>
#include "Piece.hpp"
namespace Modele
{
    class Roi : public Piece
    {
    private:
        bool aBouge_ = false; 
        static int nbRois_; // compteur de rois existants

    public:
        Roi(Position position, Couleur couleur) : Piece(position, couleur) {
            
            if(nbRois_ > 2) {
                throw std::runtime_error("Il ne peut y avoir que 2 rois dans une partie d'échecs !");
            }
            nbRois_++;
        }
        static int getNbRois() { return Roi::nbRois_; }
        ~Roi();
        char symbole() const override { return 'R'; }
        std::vector<Position> calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>> &echiquier) override;
        QString nomImage() const override
        {
            return (couleur_ == Couleur::Blanc) ? "roiBlanc" : "roiNoir";
        }
        bool aBouge() const { return aBouge_; }
        void setABouge(bool aBouge) { aBouge_ = aBouge; }
    };

}
