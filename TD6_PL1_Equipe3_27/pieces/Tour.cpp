#include "Tour.hpp"
#include "../Echiquier.hpp"
std::vector<Position> Modele::Tour::calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>> &echiquier)
{
    deplacementsPossibles_.clear();
    int x = position_.x();
    int y = position_.y();

    // 4 directions : haut, bas, gauche, droite
    const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (const auto &[dx, dy] : directions)
    {
        int nx = x + dx;
        int ny = y + dy;

        while (nx >= 0 && nx < Echiquier::N_CASES && ny >= 0 && ny < Echiquier::N_CASES)
        {
            std::shared_ptr<Piece> pieceCible = echiquier[nx][ny];
            if (pieceCible == nullptr)
            {
                deplacementsPossibles_.emplace_back(nx, ny);
            }
            else
            {
                if (pieceCible->couleur() != couleur_)
                {
                    deplacementsPossibles_.emplace_back(nx, ny);
                }
                break; 
            }
            nx += dx;
            ny += dy;
        }
    }
    return deplacementsPossibles_;
}
int Modele::Tour::nbToursBlanches_ = 0;
int Modele::Tour::nbToursNoires_ = 0;
QString Modele::Tour::nomImage() const
{
    return (couleur_ == Couleur::Blanc) ? "tourBlanc" : "tourNoir";
}
Modele::Tour::Tour(Position position, Couleur couleur) : Piece(position, couleur)
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