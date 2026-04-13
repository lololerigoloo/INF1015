#include "Pion.hpp"
#include "../Echiquier.hpp"
int Modele::Pion::nbPionsBlancs_ = 0;
int Modele::Pion::nbPionsNoirs_ = 0;
Modele::Pion::Pion(Position position, Couleur couleur) : Piece(position, couleur)
{
    if (couleur == Couleur::Blanc)
    {
        nbPionsBlancs_++;
        if (nbPionsBlancs_ > 8)
        {
            nbPionsBlancs_--;
            throw ExceptionNombrePionsBlancs();
        }
    }
    else
    {
        nbPionsNoirs_++;
        if (nbPionsNoirs_ > 8)
        {
            nbPionsNoirs_--;
            throw ExceptionNombrePionsNoirs();
        }
    }
}

std::vector<Position> Modele::Pion::calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>> &echiquier)
{
    deplacementsPossibles_.clear();
    int direction = (couleur_ == Couleur::Blanc) ? -1 : 1; // les blancs vont vers le haut, les noirs vers le bas
    int x = position_.x();
    int y = position_.y();

    // déplacement de base : une case devant
    if (x + direction >= 0 && x + direction < Echiquier::N_CASES && echiquier[x + direction][y] == nullptr)
    {
        deplacementsPossibles_.emplace_back(x + direction, y);
        // si c'est la première fois que le pion bouge, il peut avancer de deux cases
        if ((couleur_ == Couleur::Blanc && x == 6) || (couleur_ == Couleur::Noir && x == 1))
        {
            if (echiquier[x + 2 * direction][y] == nullptr)
            {
                deplacementsPossibles_.emplace_back(x + 2 * direction, y);
            }
        }
    }

    // captures possibles : diagonales
    for (int dy : {-1, 1})
    {
        if (y + dy >= 0 && y + dy < Echiquier::N_CASES && x + direction >= 0 && x + direction < Echiquier::N_CASES)
        {
            std::shared_ptr<Piece> pieceAdverse = echiquier[x + direction][y + dy];
            if (pieceAdverse != nullptr && pieceAdverse->couleur() != couleur_)
            {
                deplacementsPossibles_.emplace_back(x + direction, y + dy);
            }
        }
    }
    return deplacementsPossibles_;
}
Modele::Pion::~Pion()
{
    if (couleur_ == Couleur::Blanc)
        nbPionsBlancs_--;
    else
        nbPionsNoirs_--;
}