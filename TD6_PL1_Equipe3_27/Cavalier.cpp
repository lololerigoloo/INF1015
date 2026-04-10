#include "Cavalier.hpp"

int Modele::Cavalier::nbCavaliersBlancs_ = 0;
int Modele::Cavalier::nbCavaliersNoirs_ = 0;
QString Modele::Cavalier::nomImage() const
{
    return couleur_ == Couleur::Blanc ? "cavalierBlanc" : "cavalierNoir";
}
std::vector<Position> Modele::Cavalier::calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>> &echiquier)
{
    deplacementsPossibles_.clear();
    int x = position_.x();
    int y = position_.y();
    // Les 8 mouvements possibles du cavalier
    std::vector<std::pair<int, int>> mouvements = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    for (const auto &[dx, dy] : mouvements)
    {
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
    return deplacementsPossibles_;
}