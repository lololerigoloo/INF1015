#include "deplacementManager.hpp"

void Modele::DeplacementManager::deplacer(const Position &depart, const Position &fin)
{
    if (!echiquier_->estPositionValide(depart) || !echiquier_->estPositionValide(fin))
        return;

    std::shared_ptr<Piece> piece = echiquier_->getPiece(depart);
    if (piece == nullptr)
        return; // pas de pièce à déplacer

    // Vérifier que le déplacement est légal pour la pièce
    std::vector<Position> deplacementsPossibles = piece->calculerDeplacementsPossibles(echiquier_->getCases());
    auto it = std::find_if(deplacementsPossibles.begin(), deplacementsPossibles.end(),
                           [&fin](const Position &pos)
                           { return pos.x() == fin.x() && pos.y() == fin.y(); });
    if (it == deplacementsPossibles.end())
        return; // déplacement non autorisé pour cette pièce

    // Déplacer la pièce
    if (estEchecApresDeplacement(depart, fin))
    {
        return; // ne pas déplacer si cela met le roi en échec
    }
    if (echiquier_->getCases()[fin.x()][fin.y()] != nullptr)
    {
        echiquier_->getCases()[fin.x()][fin.y()] = piece;
    }
    echiquier_->getCases()[fin.x()][fin.y()] = piece;
    echiquier_->getCases()[depart.x()][depart.y()] = nullptr;
    piece->setPosition(fin); // mettre à jour la position de la pièce

    tour_ = (tour_ == Couleur::Blanc) ? Couleur::Noir : Couleur::Blanc;
}
void Modele::DeplacementManager::setPiecesSelectionnee(std::shared_ptr<Piece> piece)
{
    piecesSelectionnee_ = piece;
}
bool Modele::DeplacementManager::estEchecApresDeplacement(const Position &depart, const Position &fin)
{
    // Simuler le déplacement
    std::shared_ptr<Piece> piece = echiquier_->getPiece(depart);
    std::shared_ptr<Piece> pieceCapturee = echiquier_->getPiece(fin);
    echiquier_->getCases()[fin.x()][fin.y()] = piece;
    echiquier_->getCases()[depart.x()][depart.y()] = nullptr;

    // Vérifier si le roi du joueur qui a déplacé est en échec
    bool enEchec = false;
    for (const auto &ligne : echiquier_->getCases())
    {
        for (const auto &p : ligne)
        {
            if (p != nullptr && p->couleur() == tour_)
            {
                std::vector<Position> deplacementsAdverses = p->calculerDeplacementsPossibles(echiquier_->getCases());
                for (const auto &pos : deplacementsAdverses)
                {
                    std::shared_ptr<Piece> cible = echiquier_->getPiece(pos);
                    if (cible != nullptr && cible->symbole() == 'R' && cible->couleur() == tour_)
                    {
                        enEchec = true;
                        break;
                    }
                }
            }
            if (enEchec)
                break;
        }
        if (enEchec)
            break;
    }

    // Revenir à la situation initiale
    echiquier_->getCases()[depart.x()][depart.y()] = piece;
    echiquier_->getCases()[fin.x()][fin.y()] = pieceCapturee;

    return enEchec;
}
Modele::DeplacementManager::~DeplacementManager() {}
Modele::DeplacementManager::DeplacementManager(std::shared_ptr<Echiquier> echiquier) : echiquier_(echiquier) {}