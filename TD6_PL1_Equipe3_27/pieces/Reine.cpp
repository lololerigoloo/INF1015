#include "Reine.hpp"
#include "../Echiquier.hpp"
int Modele::Reine::nbReinesBlanches_ = 0;
int Modele::Reine::nbReinesNoires_ = 0;
Modele::Reine::~Reine()
{
    if (couleur_ == Couleur::Blanc)
        nbReinesBlanches_--;
    else
        nbReinesNoires_--;
}
QString Modele::Reine::nomImage() const
{
    return couleur_ == Couleur::Blanc ? "reineBlanche" : "reineNoire";
}
std::vector<Position> Modele::Reine::calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>> &echiquier)
{
    deplacementsPossibles_.clear();
    int x = position_.x();
    int y = position_.y();
    // Les 8 directions (horizontal, vertical, diagonal)
    for (int dx : {-1, 0, 1})
    {
        for (int dy : {-1, 0, 1})
        {
            if (dx == 0 && dy == 0)
                continue;

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
    }
    return deplacementsPossibles_;
}
Modele::Reine::Reine(Position position, Modele::Couleur couleur) : Piece(position, couleur)
{
    if (couleur == Modele::Couleur::Blanc)
    {
        if (nbReinesBlanches_ >= 1)
        {
            throw ExceptionReineBlanche();
        }
        nbReinesBlanches_++;
    }
    else
    {
        if (nbReinesNoires_ >= 1)
        {
            throw ExceptionReineNoire();
        }
        nbReinesNoires_++;
    }
}