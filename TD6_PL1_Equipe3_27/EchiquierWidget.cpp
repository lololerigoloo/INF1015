#include <QPainter>
#include <QMouseEvent> 
#include <QString>
#include <QDebug>
#include "EchiquierWidget.hpp"
#include "Piece.hpp"
namespace Vue {

EchiquierWidget::EchiquierWidget(std::shared_ptr<Modele::Echiquier> echiquier, QWidget* parent)
    : QWidget(parent), echiquier_(std::move(echiquier)), tailleCase_(100)
{
    // taille fixe de la fenêtre : 8 cases x 80 pixels
    setFixedSize((N_CASES+4) * tailleCase_, N_CASES * tailleCase_);
    
}

void EchiquierWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    for (int i = 0; i < N_CASES; i++) {
        for (int j = 0; j < N_CASES; j++) {
            // alterner les couleurs
            if ((i + j) % 2 == 0)
                painter.setBrush(Qt::white);
            else
                painter.setBrush(Qt::gray);

            // dessiner la case
            painter.drawRect(
                j * tailleCase_,  // x
                i * tailleCase_,  // y
                tailleCase_,      // largeur
                tailleCase_       // hauteur
            );
            auto piece = echiquier_->getPiece(Position(i, j));
            if (piece) {
                const QPixmap& px = Vue::PiecePixmapManager::instance().getPixmap(piece->nomImage());
                painter.drawPixmap(j * tailleCase_, i * tailleCase_, tailleCase_, tailleCase_, px);
            }
        }
    }
    std::shared_ptr<Modele::Piece> piecesSelectionnee = echiquier_->getPiecesSelectionnee();
    if (piecesSelectionnee)
    {
        for(const auto& pos : piecesSelectionnee->calculerDeplacementsPossibles(echiquier_->getCases()))
        {
            painter.setBrush(QColor(0, 255, 0, 100)); // vert transparent
            painter.drawEllipse(
                pos.y() * tailleCase_ + tailleCase_ / 4, // x
                pos.x() * tailleCase_ + tailleCase_ / 4, // y
                tailleCase_ / 2, // largeur
                tailleCase_ / 2  // hauteur
            );
        }
    }
    
    //dessiner la droite de l'échiquier
    painter.setBrush(Qt::blue);
    painter.drawRect(
        N_CASES * tailleCase_,  // x
        0,                      // y
        4 * tailleCase_,        // largeur
        N_CASES * tailleCase_   // hauteur
    );
}

}