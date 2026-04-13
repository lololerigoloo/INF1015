#pragma once
#include <QWidget>
#include "Echiquier.hpp"
#include <memory>
#include "piecePixmapManager.hpp"
#include "blocInfomation.hpp"
#include "pieces/Roi.hpp"
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
        void informationGenerale(const Modele::BlocInformation &info);
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
        void chargerNiveau(QString niveau);
        void afficherEchecEtMat(const Modele::Couleur &gagnant)
        {
            for (const auto &ligne : echiquier_->getCases())
            {
                for (const auto &piece : ligne)
                {
                    if (piece != nullptr && piece->symbole() == 'R')
                    {
                        std::shared_ptr<Modele::Roi> roi = std::dynamic_pointer_cast<Modele::Roi>(piece);
                        if (roi != nullptr)
                            roi->changerNomRoi(roi->couleur() == gagnant);
                    }
                }
            }
            update();
        }

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