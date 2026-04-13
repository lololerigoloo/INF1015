#include "mainWinUi.hpp"
Vue::MainWinUi::MainWinUi()
{
        echiquier_ = std::make_shared<Modele::Echiquier>();

        QWidget *central = new QWidget(this);
        QHBoxLayout *mainLayout = new QHBoxLayout(central);

        QWidget *leftContainer = new QWidget(this);
        QVBoxLayout *leftLayout = new QVBoxLayout(leftContainer);

        annonceWidget_ = std::make_unique<Vue::AnnonceWidget>(leftContainer);
        leftLayout->addWidget(annonceWidget_.get());

        echiquierWidget_ = std::make_unique<Vue::EchiquierWidget>(echiquier_);
        leftLayout->addWidget(echiquierWidget_.get());

        leftLayout->setStretch(0, 0);
        leftLayout->setStretch(1, 1);

        QWidget *sideContainer = new QWidget(this);
        QVBoxLayout *sideLayout = new QVBoxLayout(sideContainer);
        sideWidget_ = std::make_unique<Vue::SideWidget>(sideContainer);
        sideLayout->addWidget(sideWidget_.get());
        sideContainer->setStyleSheet("background-color: brown;");

        selecteurNiveau_ = std::make_unique<Vue::SelecteurDeNiveau>(this);
        connect(selecteurNiveau_.get(), &Vue::SelecteurDeNiveau::niveauSelectionne,
                echiquierWidget_.get(), &Vue::EchiquierWidget::chargerNiveau);

        mainLayout->addWidget(leftContainer);
        mainLayout->addWidget(selecteurNiveau_.get());
        mainLayout->addWidget(sideContainer);
        mainLayout->setStretch(0, 3);
        mainLayout->setStretch(1, 1);
        mainLayout->setStretch(2, 1);

        connect(echiquierWidget_.get(), &Vue::EchiquierWidget::caseCliquee,
                this, &MainWinUi::placerPiece);
        connect(echiquierWidget_.get(), &Vue::EchiquierWidget::caseCliquee,
                this, &MainWinUi::actionEffacer);
        connect(sideWidget_.get(), &Vue::SideWidget::actionLancer,
                echiquierWidget_.get(), &Vue::EchiquierWidget::partieLancee);
        connect(sideWidget_.get(), &Vue::SideWidget::selectionChangee,
                this, &MainWinUi::changerSelection);
        changerSelection(sideWidget_->pieceSelectionnee(), sideWidget_->couleurSelectionnee());
        connect(sideWidget_.get(), &Vue::SideWidget::actionReset,
                echiquierWidget_.get(), &Vue::EchiquierWidget::effacerToutPiece);
        connect(sideWidget_.get(), &Vue::SideWidget::actionLancerComplet,
                echiquierWidget_.get(), &Vue::EchiquierWidget::placerUneVraiePartie);

        connect(echiquierWidget_.get(), &Vue::EchiquierWidget::informationGenerale,
                annonceWidget_.get(), &Vue::AnnonceWidget::mettreAJourAnnonce);

        connect(sideWidget_.get(), &Vue::SideWidget::actionLancer,
                annonceWidget_.get(), &Vue::AnnonceWidget::partieLancee);
        connect(sideWidget_.get(), &Vue::SideWidget::actionReset,
                annonceWidget_.get(), &Vue::AnnonceWidget::resetAnnonce);
        connect(sideWidget_.get(), &Vue::SideWidget::selectionChangee,
                annonceWidget_.get(), &Vue::AnnonceWidget::annoncerSelection);
        connect(sideWidget_.get(), &Vue::SideWidget::actionLancerComplet,
                annonceWidget_.get(), &Vue::AnnonceWidget::partieLancee);
        connect(sideWidget_.get(), &Vue::SideWidget::actionLancerComplet,
                selecteurNiveau_.get(), [this]()
                { selecteurNiveau_->mettreActif(false); });
        connect(sideWidget_.get(), &Vue::SideWidget::actionLancer,
                selecteurNiveau_.get(), [this]()
                { selecteurNiveau_->mettreActif(false); });
        connect(sideWidget_.get(), &Vue::SideWidget::actionReset,
                selecteurNiveau_.get(), [this]()
                { selecteurNiveau_->mettreActif(true); });
        connect(selecteurNiveau_.get(), &Vue::SelecteurDeNiveau::niveauSelectionne,
                sideWidget_.get(), [this](const QString&) // ici le waring est dû au fait que le signal
                                                                 // niveauSelectionne n'envoie pas de booléen,
                                                                 // mais on sait que ça va forcer la mise à jour,
                                                                 // donc on peut ignorer le warning
                { sideWidget_->doitMettreAJour(false); });
        connect(annonceWidget_.get(), &Vue::AnnonceWidget::EchecEtMat,
                echiquierWidget_.get(), &Vue::EchiquierWidget::afficherEchecEtMat);
        
        setCentralWidget(central);
        setWindowTitle("Échecs1015");
        resize(1000, 700);
        show();
}