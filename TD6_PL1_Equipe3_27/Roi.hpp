#pragma once
#include "Position.hpp"
#include "Echiquier.hpp"
#include <vector>
#include "Piece.hpp"
#include <stdexcept>
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
        Roi(Position position, Couleur couleur) : Piece(position, couleur)
        {
            if (couleur == Couleur::Blanc)
                nbRoisBlancs_++;
            else
                nbRoisNoirs_++;

            if (nbRoisBlancs_ > 1)
            {
                nbRoisBlancs_--; // décrémenter pour compenser l'échec de la création
                throw ExceptionNombreRoisBlancs();
            }
            if (nbRoisNoirs_ > 1)
            {
                nbRoisNoirs_--; // décrémenter pour compenser l'échec de la création
                throw ExceptionNombreRoisNoirs();
            }
            if (couleur == Couleur::Blanc && position.x() == 7 && position.y() == 4)
                aBouge_ = false;
            else if (couleur == Couleur::Noir && position.x() == 0 && position.y() == 4)
                aBouge_ = false;
            else
                aBouge_ = true; // si le roi n'est pas à sa position initiale, il est considéré comme ayant déjà bougé
        }
        static int getNbRoisBlancs() { return Roi::nbRoisBlancs_; }
        static int getNbRoisNoirs() { return Roi::nbRoisNoirs_; }
        ~Roi();
        char symbole() const override { return 'R'; }
        std::vector<Position> calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>> &echiquier) override;
        QString nomImage() const override
        {
            return nomRoi_;
        }
        void changerNomRoi(bool aGagner)
        {
            if (aGagner)
                nomRoi_ = "trophee";
            else
                nomRoi_ = "perdu";
        }
        bool aBouge() const { return aBouge_; }
        void setABouge(bool aBouge) { aBouge_ = aBouge; }
        bool peutFaireRoque() const { return peutFaireRoque_; }
        void setPeutFaireRoque(bool peutFaireRoque) { peutFaireRoque_ = peutFaireRoque; }
    };

}
