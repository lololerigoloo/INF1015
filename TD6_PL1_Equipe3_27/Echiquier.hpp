#pragma once
#include <memory>
#include "Piece.hpp"
#include "Position.hpp"
#include <vector>
#include "deplacementManager.hpp"
#include "Piece.hpp"
#include "Pion.hpp"
#include "Fou.hpp"
#include "Roi.hpp"
#include "Tour.hpp"
#include "Reine.hpp"
#include "Cavalier.hpp"
#include "SideWidget.hpp"
#include "blocInfomation.hpp"
namespace Modele
{
    class Echiquier
    {
    public:
        Echiquier();
        ~Echiquier();
        void ajouterPiece(std::shared_ptr<Piece> piece);
        void ajouterPiece(Vue::TypePiece type, Couleur couleur, Position position);
        void enleverPiece(const Position &position)
        {
            if (estPositionValide(position))
                cases_[position.x()][position.y()] = nullptr;
        }
        void placerNiveau(const QString &niveau);
        Position trouverRoi(Couleur couleur) const
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
        void gererCaseCliquee(const Position &position);
        std::shared_ptr<Piece> getPiece(const Position &position) const;
        static bool estPositionValide(const Position &position)
        {
            return position.x() >= 0 && position.x() < N_CASES && position.y() >= 0 && position.y() < N_CASES;
        }
        void reset();
        void setPiecesSelectionnee(std::shared_ptr<Piece> piece) { deplacementManager_->setPiecesSelectionnee(piece); }
        std::vector<std::vector<std::shared_ptr<Piece>>> &getCases() { return cases_; }
        const std::vector<std::vector<std::shared_ptr<Piece>>> &getCases() const { return cases_; }
        std::shared_ptr<Piece> getPiecesSelectionnee() const { return deplacementManager_->getPiecesSelectionnee(); }
        static const int N_CASES = 8;
        void deplacerPiece(const Position &depart, const Position &fin);
        void placerUneVraiePartie();
        Modele::BlocInformation getBlocInformation() const
        {
            return deplacementManager_->getBlocInformation();
        }
    private:
        std::vector<std::vector<std::shared_ptr<Piece>>> cases_ = std::vector<std::vector<std::shared_ptr<Piece>>>(N_CASES, std::vector<std::shared_ptr<Piece>>(N_CASES, nullptr));
        std::unique_ptr<DeplacementManager> deplacementManager_;
    };

}