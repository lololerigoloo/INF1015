#pragma once
#include "Piece.hpp"
namespace Modele
{
    class Roi : public Piece
    {
    private:
        bool aBouge_ = false;
        bool peutFaireRoque_ = false;
        static int nbRoisBlancs_; // compteur de rois existants
        static int nbRoisNoirs_;  // compteur de rois existants
        QString nomRoi_ = (couleur_ == Couleur::Blanc) ? "roiBlanc" : "roiNoir";

    public:
        Roi(Position position, Couleur couleur);
        static int getNbRoisBlancs() { return Roi::nbRoisBlancs_; }
        static int getNbRoisNoirs() { return Roi::nbRoisNoirs_; }
        ~Roi();
        char symbole() const override { return 'R'; }
        std::vector<Position> calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>> &echiquier) override;
        QString nomImage() const override
        {
            return nomRoi_;
        }
        void changerNomRoi(bool aGagner);
        bool aBouge() const { return aBouge_; }
        void setABouge(bool aBouge) { aBouge_ = aBouge; }
        bool peutFaireRoque() const { return peutFaireRoque_; }
        void setPeutFaireRoque(bool peutFaireRoque) { peutFaireRoque_ = peutFaireRoque; }
    };

}
