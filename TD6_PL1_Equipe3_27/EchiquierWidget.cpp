#include <QPainter>
#include <QMouseEvent> 
#include "EchiquierWidget.hpp"

namespace Vue {

EchiquierWidget::EchiquierWidget(QWidget* parent)
    : QWidget(parent), tailleCase_(80)
{
    // taille fixe de la fenêtre : 8 cases x 80 pixels
    setFixedSize(N_CASES * tailleCase_, N_CASES * tailleCase_);
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
        }
    }
}

void EchiquierWidget::mousePressEvent(QMouseEvent* event) {
    // convertir la position du clic en case (colonne, rangée)
    int colonne = event->pos().x() / tailleCase_;
    int rangee  = event->pos().y() / tailleCase_;
    // ici tu sauras sur quelle case le joueur a cliqué
}

}