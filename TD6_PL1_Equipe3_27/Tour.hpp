#pragma once
#include "Piece.hpp"
#include "Position.hpp"
#include <vector>
#include "Echiquier.hpp"

namespace Modele
{

    class Tour : public Piece
    {
    public:
        ~Tour()
        {
            if (couleur_ == Couleur::Blanc)
                nbToursBlanches_--;
            else
                nbToursNoires_--;
        }
        Tour(Position position, Couleur couleur) : Piece(position, couleur)
        {
            if (couleur == Couleur::Blanc)
            {

                nbToursBlanches_++;
                if (nbToursBlanches_ > 2)
                {
                    nbToursBlanches_--;
                    throw ExceptionNombreToursBlanches();
                }
            }
            else
            {
                nbToursNoires_++;
                if (nbToursNoires_ > 2)
                {
                    nbToursNoires_--;
                    throw ExceptionNombreToursNoires();
                }
            }
            if(couleur == Couleur::Blanc && (position.x() == 7 && (position.y() == 0 || position.y() == 7)))
                aBouge_ = false;
            else if(couleur == Couleur::Noir && (position.x() == 0 && (position.y() == 0 || position.y() == 7)))
                aBouge_ = false;
            else
                aBouge_ = true; // si la tour n'est pas à sa position initiale, elle est considérée comme ayant déjà bougé
        }

        char symbole() const override { return 'T'; }
        std::vector<Position> calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>> &echiquier) override;
        QString nomImage() const override;
        bool aBouge() const { return aBouge_; }
        void setABouge(bool aBouge) { aBouge_ = aBouge; }

    private:
        bool aBouge_ = false;
        static int nbToursBlanches_; // compteur de tours existantes
        static int nbToursNoires_;   // compteur de tours existantes
    };

}