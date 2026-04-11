#include "mainWinUi.hpp"
Vue::MainWinUi::MainWinUi()
{
        echiquier_ = std::make_shared<Modele::Echiquier>();

        QWidget *central = new QWidget(this);
        QHBoxLayout *layout = new QHBoxLayout(central);

        echiquierWidget_ = std::make_unique<Vue::EchiquierWidget>(echiquier_);
        layout->addWidget(echiquierWidget_.get());

        // Connexions échiquier
        connect(echiquierWidget_.get(), &Vue::EchiquierWidget::caseCliquee,
                this, &MainWinUi::placerPiece);

        connect(echiquierWidget_.get(), &Vue::EchiquierWidget::caseCliquee,
                this, &MainWinUi::actionEffacer);
        
        QWidget *sideContainer = new QWidget(this);
        QVBoxLayout *sideLayout = new QVBoxLayout(sideContainer);

        sideWidget_ = std::make_unique<Vue::SideWidget>(sideContainer);
        sideLayout->addWidget(sideWidget_.get());
        connect(sideWidget_.get(), &Vue::SideWidget::actionLancer,
                echiquierWidget_.get(), &Vue::EchiquierWidget::partieLancee);
        

        layout->addWidget(sideContainer);

        layout->setStretch(0, 3);
        layout->setStretch(1, 1);

        sideContainer->setStyleSheet("background-color: brown;");

        setCentralWidget(central);

        setWindowTitle("Échecs1015");
        resize(800, 600);

        connect(sideWidget_.get(), &Vue::SideWidget::selectionChangee,
                this, &MainWinUi::changerSelection);                                            // ici il faut le faire manuellement la premiere fois parce que le constructeur de SideWidget initialise pieceSelectionnee_ et couleurSelectionnee_
                                                                                                // à des valeurs par défaut qui ne sont pas forcément les mêmes que celles de MainWinUi
        changerSelection(sideWidget_->pieceSelectionnee(), sideWidget_->couleurSelectionnee()); // forcer la synchronisation initiale
        connect(sideWidget_.get(), &Vue::SideWidget::actionReset,
                echiquierWidget_.get(), &Vue::EchiquierWidget::effacerToutPiece);
        connect(sideWidget_.get(), &Vue::SideWidget::actionLancerComplet,
                echiquierWidget_.get(), &Vue::EchiquierWidget::placerUneVraiePartie);

        show();
}