#include "Fou.hpp"

std::vector<Position> Modele::Fou::calculerDeplacementsPossibles(const std::vector<std::vector<std::shared_ptr<Piece>>>& echiquier) {
    deplacementsPossibles_.clear();
    int x = position_.x();
    int y = position_.y();

    // Les 4 directions diagonales
    for (int dx : {-1, 1}) {
        for (int dy : {-1, 1}) {
            int nx = x + dx;
            int ny = y + dy;

            while (nx >= 0 && nx < Echiquier::N_CASES && ny >= 0 && ny < Echiquier::N_CASES) {
                std::shared_ptr<Piece> pieceCible = echiquier[nx][ny];
                if (pieceCible == nullptr) {
                    deplacementsPossibles_.emplace_back(nx, ny);
                } else {
                    if (pieceCible->couleur() != couleur_) {
                        deplacementsPossibles_.emplace_back(nx, ny);
                    }
                    break; // on ne peut pas sauter par-dessus une pièce
                }
                nx += dx;
                ny += dy;
            }
        }
    }
    return deplacementsPossibles_;
}
int Modele::Fou::nbFousBlancs_ = 0;
int Modele::Fou::nbFousNoirs_ = 0;
Modele::Fou::~Fou()
{
    couleur_ == Couleur::Blanc ? nbFousBlancs_-- : nbFousNoirs_--;
}