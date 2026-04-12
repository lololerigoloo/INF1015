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
    if (aBouge_ == false)
    {
        int ligne = position_.x();

        // Roque long
        if (echiquier[ligne][1] == nullptr && echiquier[ligne][2] == nullptr && echiquier[ligne][3] == nullptr && echiquier[ligne][0] != nullptr && echiquier[ligne][4] != nullptr && echiquier[ligne][4]->symbole() == 'R' && !static_cast<Roi *>(echiquier[ligne][4].get())->aBouge())
        {
            std::shared_ptr<Piece> tourGauche = echiquier[ligne][0];
            if (tourGauche->symbole() == 'T' && !static_cast<Tour *>(tourGauche.get())->aBouge())
            {
                deplacementsPossibles_.emplace_back(ligne, 2);
                peutFaireRoque_ = true;
            }
        }

        // Roque court
        if (echiquier[ligne][5] == nullptr && echiquier[ligne][6] == nullptr && echiquier[ligne][7] != nullptr && echiquier[ligne][4] != nullptr && echiquier[ligne][4]->symbole() == 'R' && !static_cast<Roi *>(echiquier[ligne][4].get())->aBouge())
        {
            std::shared_ptr<Piece> tourDroite = echiquier[ligne][7];
            if (tourDroite->symbole() == 'T' && !static_cast<Tour *>(tourDroite.get())->aBouge())
            {
                deplacementsPossibles_.emplace_back(ligne, 6);
                peutFaireRoque_ = true;
            }
        }
    }
    else
    {
        peutFaireRoque_ = false;
    }
    return deplacementsPossibles_;
}
int Modele::Roi::nbRoisBlancs_ = 0;
int Modele::Roi::nbRoisNoirs_ = 0;
Modele::Roi::~Roi()
{
    couleur_ == Couleur::Blanc ? nbRoisBlancs_-- : nbRoisNoirs_--;
}