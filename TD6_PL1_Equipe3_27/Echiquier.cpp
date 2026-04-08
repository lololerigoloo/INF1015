#include "Echiquier.hpp"
#include <memory>
#include "Piece.hpp"

void Modele::Echiquier::ajouterPiece(std::shared_ptr<Piece> piece)
{
    Position pos = piece->position();
    if (this->estPositionValide(pos))
    {
        cases_[pos.x()][pos.y()] = piece;
    }
}

std::shared_ptr<Modele::Piece> Modele::Echiquier::getPiece(const Position& position) const
{
    if (Modele::Echiquier::estPositionValide(position))
    {
        return cases_[position.x()][position.y()];
    }
    return nullptr;
}
Modele::Echiquier::Echiquier() {
    cases_ = std::vector<std::vector<std::shared_ptr<Piece>>>(N_CASES, std::vector<std::shared_ptr<Piece>>(N_CASES, nullptr));
}
Modele::Echiquier::~Echiquier() {
    // Les shared_ptr s'occupent de libérer la mémoire des pièces automatiquement, donc pas besoin de faire quoi que ce soit ici.
}
void Modele::Echiquier::deplacerPiece(const Position& depart, const Position& fin)
{
   deplacementManager_->deplacer(depart, fin);
}