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
void Modele::Echiquier::ajouterPiece(Vue::TypePiece type, Couleur couleur, Position position)
{
    if (!estPositionValide(position))
        return;
    if (cases_[position.x()][position.y()] != nullptr)
        return;
    try
    {
        switch (type)
        {
        case Vue::TypePiece::Pion:
            ajouterPiece(std::make_shared<Pion>(position, couleur));
            break;
        case Vue::TypePiece::Fou:
            ajouterPiece(std::make_shared<Fou>(position, couleur));
            break;
        case Vue::TypePiece::Roi:
            ajouterPiece(std::make_shared<Roi>(position, couleur));
            break;
        case Vue::TypePiece::Tour:
            ajouterPiece(std::make_shared<Tour>(position, couleur));
            break;
        default:
            break;
        }
    }
    catch (const std::runtime_error& e)
    {
        qDebug() << "Erreur lors de l'ajout d'un roi : " << e.what();
    }
}
    std::shared_ptr<Modele::Piece> Modele::Echiquier::getPiece(const Position &position) const
    {
        if (Modele::Echiquier::estPositionValide(position))
        {
            return cases_[position.x()][position.y()];
        }
        return nullptr;
    }
    Modele::Echiquier::Echiquier()
    {
        cases_ = std::vector<std::vector<std::shared_ptr<Piece>>>(N_CASES, std::vector<std::shared_ptr<Piece>>(N_CASES, nullptr));
        deplacementManager_ = std::make_unique<DeplacementManager>(this);
    }
    Modele::Echiquier::~Echiquier()
    {
        // Les shared_ptr s'occupent de libérer la mémoire des pièces automatiquement, donc pas besoin de faire quoi que ce soit ici.
    }
    void Modele::Echiquier::deplacerPiece(const Position &depart, const Position &fin)
    {
        deplacementManager_->deplacer(depart, fin);
    }
    void Modele::Echiquier::reset()
    {
        cases_ = std::vector<std::vector<std::shared_ptr<Piece>>>(N_CASES, std::vector<std::shared_ptr<Piece>>(N_CASES, nullptr));
        deplacementManager_->setPiecesSelectionnee(nullptr);
    }