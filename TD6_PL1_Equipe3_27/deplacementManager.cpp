#include "deplacementManager.hpp"
#include "Echiquier.hpp"

void Modele::DeplacementManager::deplacer(const Position &depart, const Position &fin)
{
    if (!echiquier_->estPositionValide(depart) || !echiquier_->estPositionValide(fin))
        return;

    std::shared_ptr<Piece> piece = echiquier_->getPiece(depart);
    if (piece == nullptr)
        return;

    std::vector<Position> deplacementsPossibles = piece->calculerDeplacementsPossibles(echiquier_->getCases());
    auto it = std::find_if(deplacementsPossibles.begin(), deplacementsPossibles.end(),
                           [&fin](const Position &pos)
                           { return pos.x() == fin.x() && pos.y() == fin.y(); });
    if (it == deplacementsPossibles.end())
        return;

    if (estEchecApresDeplacement(depart, fin))
        return;

    echiquier_->getCases()[fin.x()][fin.y()] = piece;
    echiquier_->getCases()[depart.x()][depart.y()] = nullptr;
    piece->setPosition(fin);
}

bool Modele::DeplacementManager::estMouvementValide(const Position &depart, const Position &fin)
{
    if (!echiquier_->estPositionValide(depart) || !echiquier_->estPositionValide(fin))
        return false;

    std::shared_ptr<Piece> piece = echiquier_->getPiece(depart);
    if (piece == nullptr)
        return false;

    std::vector<Position> deplacementsPossibles = piece->calculerDeplacementsPossibles(echiquier_->getCases());
    auto it = std::find_if(deplacementsPossibles.begin(), deplacementsPossibles.end(),
                           [&fin](const Position &pos)
                           { return pos.x() == fin.x() && pos.y() == fin.y(); });
    return it != deplacementsPossibles.end();
}

void Modele::DeplacementManager::gererCaseCliquee(const Position &position)
{
    if (getPiecesSelectionnee() != nullptr)
    {
        if (echiquier_->getPiece(position) != nullptr &&
            echiquier_->getPiece(position)->couleur() == getPiecesSelectionnee()->couleur())
        {
            setPiecesSelectionnee(echiquier_->getPiece(position));
        }
        else
        {
            if (estEchecApresDeplacement(getPiecesSelectionnee()->position(), position))
            {
                qDebug() << "Déplacement interdit : met le roi en échec";
                setPiecesSelectionnee(nullptr);
                echiquier_->setPiecesSelectionnee(nullptr);
                return;
            }
            if (estMouvementValide(getPiecesSelectionnee()->position(), position))
            {
                deplacer(getPiecesSelectionnee()->position(), position);
                ChangerTour();
            }
            else
            {
                qDebug() << "Déplacement invalide pour cette pièce";
            }
            setPiecesSelectionnee(nullptr);
            echiquier_->setPiecesSelectionnee(nullptr);
        }
    }
    else
    {
        if (echiquier_->getPiece(position) != nullptr &&
            echiquier_->getPiece(position)->couleur() == tour_)
        {
            setPiecesSelectionnee(echiquier_->getPiece(position));
        }
    }
}

bool Modele::DeplacementManager::estEchecApresDeplacement(const Position &depart, const Position &fin)
{
    std::shared_ptr<Piece> piece = echiquier_->getPiece(depart);
    std::shared_ptr<Piece> pieceCapturee = echiquier_->getPiece(fin);

    // Simuler le déplacement
    echiquier_->getCases()[fin.x()][fin.y()] = piece;
    echiquier_->getCases()[depart.x()][depart.y()] = nullptr;
    piece->setPosition(fin);

    bool enEchec = estEchec(piece->couleur());

    // Restaurer la situation initiale
    echiquier_->getCases()[depart.x()][depart.y()] = piece;
    echiquier_->getCases()[fin.x()][fin.y()] = pieceCapturee;
    piece->setPosition(depart);

    return enEchec;
}

bool Modele::DeplacementManager::estEchec(const Couleur &couleur)
{
    try
    {
        Position positionRoi = echiquier_->trouverRoi(couleur);

        for (const auto &ligne : echiquier_->getCases())
        {
            for (const auto &p : ligne)
            {
                if (p != nullptr && p->couleur() != couleur)
                {
                    std::vector<Position> deplacementsAdverses = p->calculerDeplacementsPossibles(echiquier_->getCases());
                    for (const auto &pos : deplacementsAdverses)
                    {
                        if (pos.x() == positionRoi.x() && pos.y() == positionRoi.y())
                            return true;
                    }
                }
            }
        }
    }
    catch (const std::runtime_error &e)
    {
        qDebug() << "Erreur lors de la vérification de l'échec : " << e.what();
        return false;
    }
    return false;
}

bool Modele::DeplacementManager::estEchecEtMat(const Couleur &couleur)
{
    if (!estEchec(couleur))
        return false;

    try
    {
        for (int i = 0; i < Echiquier::N_CASES; i++)
        {
            for (int j = 0; j < Echiquier::N_CASES; j++)
            {
                std::shared_ptr<Piece> piece = echiquier_->getCases()[i][j];
                if (piece != nullptr && piece->couleur() == couleur)
                {
                    std::vector<Position> deplacementsPossibles = piece->calculerDeplacementsPossibles(echiquier_->getCases());
                    for (const auto &pos : deplacementsPossibles)
                    {
                        if (!estEchecApresDeplacement(piece->position(), pos))
                            return false; // au moins un mouvement légal existe
                    }
                }
            }
        }
    }
    catch (const std::runtime_error &e)
    {
        qDebug() << "Erreur lors de la vérification de l'échec et mat : " << e.what();
        return false;
    }

    return true;
}

Modele::DeplacementManager::~DeplacementManager() {}