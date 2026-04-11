#pragma once
#include <QWidget>
#include "Echiquier.hpp"
#include <memory>
#include "piecePixmapManager.hpp"
namespace Vue
{

    class EchiquierWidget : public QWidget
    {
        Q_OBJECT
    public:
        EchiquierWidget(std::shared_ptr<Modele::Echiquier> echiquier, QWidget *parent = nullptr);
        int tailleCase() const { return tailleCase_; }
        void mousePressEvent(QMouseEvent *event) override;
        void resizeEvent(QResizeEvent *event) override;
    signals:
        void caseCliquee(const Position &position);
    public slots:
        void effacerToutPiece();
        void placerUneVraiePartie()
        {
            estPartieEnCours_ = true;
            echiquier_->placerUneVraiePartie();
            update();
        }
        void partieLancee()
        {
            estPartieEnCours_ = true;
            qDebug() << "Partie lancée";
        }
        void gererCaseCliquee(const Position &position);

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        QWidget *parent_;
        std::shared_ptr<Modele::Echiquier> echiquier_;
        static const int N_CASES = 8;
        int tailleCase_;
        bool estPartieEnCours_ = false;
        bool estTourBlanc_ = true;
    };

}