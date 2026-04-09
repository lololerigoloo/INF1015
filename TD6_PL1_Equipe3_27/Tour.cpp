#include "Tour.hpp"

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
QString Modele::Tour::nomImage() const
{
    return (couleur_ == Couleur::Blanc) ? "tourBlanc" : "tourNoir";
}