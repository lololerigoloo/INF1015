#include "mainWinUi.hpp"
#include <QMouseEvent>
#include "Piece.hpp"
#include "Pion.hpp"
#include "Fou.hpp"
#include "Roi.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
Vue::MainWinUi::MainWinUi()
{
    echiquier_ = std::make_shared<Modele::Echiquier>();


    QWidget *central = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(central);


    echiquierWidget_ = std::make_unique<Vue::EchiquierWidget>(echiquier_);
    layout->addWidget(echiquierWidget_.get());
    connect(echiquierWidget_.get(), &Vue::EchiquierWidget::caseCliquee,
        this, &MainWinUi::placerPiece);
    connect(echiquierWidget_.get(), &Vue::EchiquierWidget::caseCliquee,
        this, &MainWinUi::actionEffacer);

    QWidget *sideWidget = new QWidget(this);
    QVBoxLayout *sideLayout = new QVBoxLayout(sideWidget);

    sideWidget_ = std::make_unique<Vue::SideWidget>(sideWidget);
    sideLayout->addWidget(sideWidget_.get());

    sideWidget->setFixedWidth(200);
    sideWidget->setStyleSheet("background-color: brown;");

    layout->addWidget(sideWidget);

    setCentralWidget(central);

    setWindowTitle("Échecs1015");
    resize(800, 600);

    connect(sideWidget_.get(), &Vue::SideWidget::selectionChangee,
            this, &MainWinUi::changerSelection);

    show();
}
