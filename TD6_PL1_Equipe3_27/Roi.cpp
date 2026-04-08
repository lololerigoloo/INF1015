#include "Roi.hpp"
std::vector<Position> Modele::Roi::calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>> &echiquier)
{
    deplacementsPossibles_.clear();
    int x = position_.x();
    int y = position_.y();

    // Les 8 cases autour du roi
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            if (dx == 0 && dy == 0)
                continue; // on ne regarde pas la case où se trouve le roi

            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < Echiquier::N_CASES && ny >= 0 && ny < Echiquier::N_CASES)
            {
                std::shared_ptr<Piece> pieceCible = echiquier[nx][ny];
                if (pieceCible == nullptr || pieceCible->couleur() != couleur_)
                {
                    deplacementsPossibles_.emplace_back(nx, ny);
                }
            }
        }
    }
    return deplacementsPossibles_;
}