#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include "Echiquier.hpp"
#include "deplacementManager.hpp"
#include "Piece.hpp"
#include <QDebug>
#include "Piece.hpp"
#include "blocInfomation.hpp"

namespace Vue
{
    class AnnonceWidget : public QWidget
    {
        Q_OBJECT
    public:
        AnnonceWidget(QWidget *parent = nullptr);
        QString transformerCouleurEnTexte(const Modele::Couleur &couleur);
    public slots:
        void mettreAJourAnnonce(const Modele::BlocInformation &info);
        void resetAnnonce()
        {
            label_->setText("Bienvenue dans le jeu d'échecs !");
            labelTour_->setText(" Choisissez un mode pour commencer une partie !");
        }
        void partieLancee()
        {
            label_->setText("");
            labelTour_->setText("C'est au tour des Blancs");
        }
        void annoncerSelection(const Vue::TypePiece &typePiece, const Modele::Couleur &couleur)
        {
            QString texte = QString("Sélection: %1 %2").arg(typePiece == Vue::TypePiece::Pion ? "Pion" : typePiece == Vue::TypePiece::Fou ? "Fou"
                                                                                                     : typePiece == Vue::TypePiece::Roi   ? "Roi"
                                                                                                     : typePiece == Vue::TypePiece::Tour  ? "Tour"
                                                                                                     : typePiece == Vue::TypePiece::Reine ? "Reine"
                                                                                                                                          : "Cavalier")
            .arg(transformerCouleurEnTexte(couleur));
                label_->setText(texte);
        }
    signals:
        void EchecEtMat(const Modele::Couleur &gagnant);
    private:
        QLabel *label_;
        QLabel *labelTour_;
    };
}