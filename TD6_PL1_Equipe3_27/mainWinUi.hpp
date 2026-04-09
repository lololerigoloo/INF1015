#pragma once
#include <QMainWindow>
#include "EchiquierWidget.hpp"
#include <memory>
#include "Echiquier.hpp"
#include <QPixmap>
#include <QLabel>
#include "SideWidget.hpp"
namespace Vue
{
    class MainWinUi : public QMainWindow
    {
        Q_OBJECT
    public:
        MainWinUi();
    public slots:
        void placerPiece(const Position &position)
        {
            if(!echiquier_->estPositionValide(position) || !sideWidget_->estActif() || sideWidget_->modeCourant() != Mode::Placer)
                return;
            qDebug() << "Placer pièce en" << position.x() << position.y();
            echiquierWidget_->update();
        }
        void actionEffacer(const Position &position)
        {
            if(!echiquier_->estPositionValide(position) || !sideWidget_->estActif() || sideWidget_->modeCourant() != Mode::Effacer)
                return;
            qDebug() << "Action Effacer";
            echiquierWidget_->update();
        }

        void changerSelection(Vue::TypePiece piece, Modele::Couleur couleur)
        {
            pieceSelectionnee_ = piece;
            couleurSelectionnee_ = couleur;

            qDebug() << "Selection changée";
        }

    private:
        std::shared_ptr<Modele::Echiquier> echiquier_;
        std::unique_ptr<Vue::EchiquierWidget> echiquierWidget_;
        std::unique_ptr<Vue::SideWidget> sideWidget_;
        Vue::TypePiece pieceSelectionnee_;
        Modele::Couleur couleurSelectionnee_;
    };
}