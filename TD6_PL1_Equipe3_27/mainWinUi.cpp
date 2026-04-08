#include "mainWinUi.hpp"
#include <QMouseEvent>
#include "Piece.hpp"
#include "Pion.hpp"
#include "Fou.hpp"
#include "Roi.hpp"
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
    if(rangee < 0 || rangee >= Modele::Echiquier::N_CASES || colonne < 0 || colonne >= Modele::Echiquier::N_CASES)
    {
        qDebug() << "Clic en dehors de l'échiquier";
        return;
    }
    else
    {
        qDebug() << "Clic sur la case (" << colonne << "," << rangee << ")";
        
    }
    echiquierWidget_->update(); // redessiner l'échiquier pour afficher la nouvelle pièce
    // ici tu sauras sur quelle case le joueur a cliqué
}