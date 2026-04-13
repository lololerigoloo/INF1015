#include "Echiquier.hpp"
#include "deplacementManager.hpp"

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
        case Vue::TypePiece::Reine:
            ajouterPiece(std::make_shared<Reine>(position, couleur));
            break;
        case Vue::TypePiece::Cavalier:
            ajouterPiece(std::make_shared<Cavalier>(position, couleur));
            break;
        default:
            break;
        }
    }
    catch (const std::runtime_error &e)
    {
        qDebug() << "Erreur lors de l'ajout d'une pièce : " << e.what();
        qDebug() << "Type de pièce : " << static_cast<int>(type) << ", Couleur : " << static_cast<int>(couleur);
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
    deplacementManager_->setTour(Couleur::Blanc);
    deplacementManager_->setPiecesSelectionnee(nullptr);
}
void Modele::Echiquier::gererCaseCliquee(const Position &position)
{
    deplacementManager_->gererCaseCliquee(position);
}
void Modele::Echiquier::placerUneVraiePartie()
{
    reset();
    // Placer les pièces blanches
    ajouterPiece(Vue::TypePiece::Tour, Couleur::Blanc, Position(7, 0));
    ajouterPiece(Vue::TypePiece::Cavalier, Couleur::Blanc, Position(7, 1));
    ajouterPiece(Vue::TypePiece::Fou, Couleur::Blanc, Position(7, 2));
    ajouterPiece(Vue::TypePiece::Reine, Couleur::Blanc, Position(7, 3));
    ajouterPiece(Vue::TypePiece::Roi, Couleur::Blanc, Position(7, 4));
    ajouterPiece(Vue::TypePiece::Fou, Couleur::Blanc, Position(7, 5));
    ajouterPiece(Vue::TypePiece::Cavalier, Couleur::Blanc, Position(7, 6));
    ajouterPiece(Vue::TypePiece::Tour, Couleur::Blanc, Position(7, 7));
    for (int i = 0; i < N_CASES; i++)
        ajouterPiece(Vue::TypePiece::Pion, Couleur::Blanc, Position(6, i));

    // Placer les pièces noires
    ajouterPiece(Vue::TypePiece::Tour, Couleur::Noir, Position(0, 0));
    ajouterPiece(Vue::TypePiece::Cavalier, Couleur::Noir, Position(0, 1));
    ajouterPiece(Vue::TypePiece::Fou, Couleur::Noir, Position(0, 2));
    ajouterPiece(Vue::TypePiece::Reine, Couleur::Noir, Position(0, 3));
    ajouterPiece(Vue::TypePiece::Roi, Couleur::Noir, Position(0, 4));
    ajouterPiece(Vue::TypePiece::Fou, Couleur::Noir, Position(0, 5));
    ajouterPiece(Vue::TypePiece::Cavalier, Couleur::Noir, Position(0, 6));
    ajouterPiece(Vue::TypePiece::Tour, Couleur::Noir, Position(0, 7));
    for (int i = 0; i < N_CASES; i++)
        ajouterPiece(Vue::TypePiece::Pion, Couleur::Noir, Position(1, i));
}

void Modele::Echiquier::placerNiveau(const QString &niveau)
{
    reset();

    if (niveau == "Mat du couloir")
    {
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Blanc, Position(7, 4));
        ajouterPiece(Vue::TypePiece::Tour, Couleur::Blanc, Position(1, 0));
        ajouterPiece(Vue::TypePiece::Tour, Couleur::Blanc, Position(3, 7));
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Noir, Position(0, 4));
        deplacementManager_->setTour(Couleur::Noir);
    }
    else if (niveau == "Mat de l'escalier")
    {
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Blanc, Position(7, 7));
        ajouterPiece(Vue::TypePiece::Tour, Couleur::Blanc, Position(4, 0));
        ajouterPiece(Vue::TypePiece::Tour, Couleur::Blanc, Position(5, 1));
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Noir, Position(0, 3));
        deplacementManager_->setTour(Couleur::Noir);
    }
    else if (niveau == "Mat du berger")
    {
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Blanc, Position(7, 4));
        ajouterPiece(Vue::TypePiece::Reine, Couleur::Blanc, Position(7, 3));
        ajouterPiece(Vue::TypePiece::Fou, Couleur::Blanc, Position(4, 2));
        ajouterPiece(Vue::TypePiece::Cavalier, Couleur::Blanc, Position(5, 5));
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Noir, Position(0, 4));
        ajouterPiece(Vue::TypePiece::Cavalier, Couleur::Noir, Position(2, 2));
        ajouterPiece(Vue::TypePiece::Cavalier, Couleur::Noir, Position(2, 5));
        ajouterPiece(Vue::TypePiece::Pion, Couleur::Noir, Position(3, 4));
        ajouterPiece(Vue::TypePiece::Pion, Couleur::Noir, Position(1, 5));
        deplacementManager_->setTour(Couleur::Blanc);
    }
    else if (niveau == "Mat de l'épaulette")
    {
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Blanc, Position(7, 4));
        ajouterPiece(Vue::TypePiece::Reine, Couleur::Blanc, Position(2, 7));
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Noir, Position(0, 4));
        ajouterPiece(Vue::TypePiece::Tour, Couleur::Noir, Position(0, 3));
        ajouterPiece(Vue::TypePiece::Tour, Couleur::Noir, Position(0, 5));
        deplacementManager_->setTour(Couleur::Blanc);
    }
    else if (niveau == "Mat de Légal")
    {
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Blanc, Position(7, 4));
        ajouterPiece(Vue::TypePiece::Fou, Couleur::Blanc, Position(1, 5));
        ajouterPiece(Vue::TypePiece::Cavalier, Couleur::Blanc, Position(5, 2));
        ajouterPiece(Vue::TypePiece::Cavalier, Couleur::Blanc, Position(3, 4));
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Noir, Position(1, 4));
        ajouterPiece(Vue::TypePiece::Cavalier, Couleur::Noir, Position(2, 2));
        ajouterPiece(Vue::TypePiece::Fou, Couleur::Noir, Position(7, 3));
        ajouterPiece(Vue::TypePiece::Pion, Couleur::Noir, Position(2, 3));
        deplacementManager_->setTour(Couleur::Blanc);
    }
    else if (niveau == "Mat des Arabes")
    {
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Blanc, Position(5, 4));
        ajouterPiece(Vue::TypePiece::Tour, Couleur::Blanc, Position(2, 0));
        ajouterPiece(Vue::TypePiece::Cavalier, Couleur::Blanc, Position(3, 6));
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Noir, Position(0, 7));
        deplacementManager_->setTour(Couleur::Blanc);
    }
    else if (niveau == "Finale Tour vs Roi")
    {
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Blanc, Position(7, 4));
        ajouterPiece(Vue::TypePiece::Tour, Couleur::Blanc, Position(4, 0));
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Noir, Position(0, 4));
        deplacementManager_->setTour(Couleur::Blanc);
    }
    else if (niveau == "Finale Dame vs Roi")
    {
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Blanc, Position(7, 4));
        ajouterPiece(Vue::TypePiece::Reine, Couleur::Blanc, Position(4, 3));
        ajouterPiece(Vue::TypePiece::Roi, Couleur::Noir, Position(0, 4));
        deplacementManager_->setTour(Couleur::Blanc);
    }
}

void Modele::Echiquier::setPiecesSelectionnee(std::shared_ptr<Piece> piece)
{
    deplacementManager_->setPiecesSelectionnee(piece);
}

std::shared_ptr<Modele::Piece> Modele::Echiquier::getPiecesSelectionnee() const
{
    return deplacementManager_->getPiecesSelectionnee();
}

Modele::BlocInformation Modele::Echiquier::getBlocInformation() const
{
    return deplacementManager_->getBlocInformation();
}
Position Modele::Echiquier::trouverRoi(Couleur couleur) const
{
    for (int i = 0; i < N_CASES; i++)
    {
        for (int j = 0; j < N_CASES; j++)
        {
            auto piece = cases_[i][j];
            if (piece != nullptr && piece->symbole() == 'R' && piece->couleur() == couleur)
            {
                return Position(i, j);
            }
        }
    }
    throw std::runtime_error("Roi non trouvé sur l'échiquier");
}