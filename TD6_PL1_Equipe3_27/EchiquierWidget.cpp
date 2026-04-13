#include <QPainter>
#include <QMouseEvent>
#include <QString>
#include <QDebug>
#include "EchiquierWidget.hpp"
#include "pieces/Piece.hpp"
namespace Vue
{

    EchiquierWidget::EchiquierWidget(std::shared_ptr<Modele::Echiquier> echiquier, QWidget *parent)
        : QWidget(parent), echiquier_(std::move(echiquier)), tailleCase_(100)
    {
        connect(this, &EchiquierWidget::caseCliquee, this, &EchiquierWidget::gererCaseCliquee);
    }

    void Vue::EchiquierWidget::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);

        for (int i = 0; i < N_CASES; i++)
        {
            for (int j = 0; j < N_CASES; j++)
            {
                // alterner les couleurs
                if ((i + j) % 2 == 0)
                    painter.setBrush(Qt::white);
                else
                    painter.setBrush(Qt::gray);

                // dessiner la case
                painter.drawRect(
                    j * tailleCase_, // x
                    i * tailleCase_, // y
                    tailleCase_,     // largeur
                    tailleCase_      // hauteur
                );
                auto piece = echiquier_->getPiece(Position(i, j));
                if (piece)
                {
                    const QPixmap &px = Vue::PiecePixmapManager::instance().getPixmap(piece->nomImage());
                    painter.drawPixmap(j * tailleCase_, i * tailleCase_, tailleCase_, tailleCase_, px);
                }
            }
        }
        std::shared_ptr<Modele::Piece> piecesSelectionnee = echiquier_->getPiecesSelectionnee();
        if (piecesSelectionnee)
        {
            for (const auto &pos : piecesSelectionnee->calculerDeplacementsPossibles(echiquier_->getCases()))
            {
                painter.setBrush(QColor(0, 255, 0, 100)); // vert transparent
                painter.drawEllipse(
                    pos.y() * tailleCase_ + tailleCase_ / 4, // x
                    pos.x() * tailleCase_ + tailleCase_ / 4, // y
                    tailleCase_ / 2,                         // largeur
                    tailleCase_ / 2                          // hauteur
                );
            }
        }
    }
    void Vue::EchiquierWidget::mousePressEvent(QMouseEvent *event)
    {
        // convertir la position du clic en case (colonne, rangée)
        int colonne = event->pos().x() / tailleCase();
        int rangee = event->pos().y() / tailleCase();
        if (rangee < 0 || rangee >= Modele::Echiquier::N_CASES || colonne < 0 || colonne >= Modele::Echiquier::N_CASES)
        {
            qDebug() << "Clic en dehors de l'échiquier";
            return;
        }
        else
        {
            emit caseCliquee(Position(rangee, colonne));
            if (estPartieEnCours_)
                emit informationGenerale(echiquier_->getBlocInformation());
            qDebug() << "Clic sur la case (" << rangee << "," << colonne << ")";
        }
        update(); // redessiner l'échiquier pour afficher la nouvelle pièce
    }
    void Vue::EchiquierWidget::resizeEvent(QResizeEvent *event)
    {
        QWidget::resizeEvent(event);
        int newTailleCase = std::min(width(), height()) / N_CASES;
        if (newTailleCase != tailleCase_)
        {
            tailleCase_ = newTailleCase;
            PiecePixmapManager::instance().setTailleCase(tailleCase_);
            update();
        }
    }
    void Vue::EchiquierWidget::gererCaseCliquee(const Position &position)
    {
        if (!estPartieEnCours_)
        {
            qDebug() << "La partie n'est pas encore lancée. Cliquez sur 'Lancer la partie' pour commencer.";
            return;
        }
        echiquier_->gererCaseCliquee(position);
        update(); // redessiner l'échiquier pour afficher les changements
    }
    void Vue::EchiquierWidget::effacerToutPiece()
    {
        echiquier_->reset();
        estPartieEnCours_ = false;
        update(); // big brain si tu update pas, les pièces ne seront pas effacées visuellement 67 on top
        qDebug() << "Effacer toutes les pièces";
    }
    void Vue::EchiquierWidget::chargerNiveau(QString niveau)
    {
        estPartieEnCours_ = true;
        
        echiquier_->placerNiveau(niveau);
        emit informationGenerale(echiquier_->getBlocInformation());
        update();
    }
}