#include "mainWinUi.hpp"
#include <QMouseEvent>  

Vue::MainWinUi::MainWinUi()
{
    echiquier_ = std::make_shared<Modele::Echiquier>();
    echiquierWidget_ = std::make_unique<Vue::EchiquierWidget>(echiquier_, this);
    setCentralWidget(echiquierWidget_.get());
    setWindowTitle("Échecs1015");
    show();
}

void Vue::MainWinUi::mousePressEvent(QMouseEvent *event)
{
    // convertir la position du clic en case (colonne, rangée)
    int colonne = event->pos().x() / echiquierWidget_->tailleCase();
    int rangee = event->pos().y() / echiquierWidget_->tailleCase();
    qDebug() << "Clic sur la case (" << rangee << ", " << colonne << ")";
    auto piece = echiquier_->getPiece(Position(rangee, colonne));
    if (piece)
        qDebug() << "tu as cliqué sur la pièce :" << piece->symbole();
    else
        qDebug() << "tu as cliqué sur la pièce : aucune";
    // ici tu sauras sur quelle case le joueur a cliqué
}
