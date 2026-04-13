// ============================================================
// Cavalier.cpp — Implémentation du Cavalier
// ============================================================
#include "Cavalier.hpp"
#include "../Echiquier.hpp"

int Modele::Cavalier::nbCavaliersBlancs_ = 0;
int Modele::Cavalier::nbCavaliersNoirs_ = 0;

Modele::Cavalier::Cavalier(Position position, Couleur couleur) : Piece(position, couleur)
{
    if (couleur == Couleur::Blanc)
    {
        nbCavaliersBlancs_++;
        if (nbCavaliersBlancs_ > 2)
        {
            nbCavaliersBlancs_--;
            throw ExceptionCavalierBlancs();
        }
    }
    else
    {
        nbCavaliersNoirs_++;
        if (nbCavaliersNoirs_ > 2)
        {
            nbCavaliersNoirs_--;
            throw ExceptionCavalierNoirs();
        }
    }
}

Modele::Cavalier::~Cavalier()
{
    couleur_ == Couleur::Blanc ? nbCavaliersBlancs_-- : nbCavaliersNoirs_--;
}

QString Modele::Cavalier::nomImage() const
{
    return couleur_ == Couleur::Blanc ? "cavalierBlanc" : "cavalierNoir";
}

std::vector<Position> Modele::Cavalier::calculerDeplacementsPossibles(
    const std::vector<std::vector<std::shared_ptr<Piece>>> &echiquier)
{
    deplacementsPossibles_.clear();
    int x = position_.x(), y = position_.y();
    for (const auto &[dx, dy] : std::vector<std::pair<int, int>>{{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}})
    {
        int nx = x + dx, ny = y + dy;
        if (nx >= 0 && nx < Echiquier::N_CASES && ny >= 0 && ny < Echiquier::N_CASES)
        {
            auto cible = echiquier[nx][ny];
            if (!cible || cible->couleur() != couleur_)
                deplacementsPossibles_.emplace_back(nx, ny);
        }
    }
    return deplacementsPossibles_;
}