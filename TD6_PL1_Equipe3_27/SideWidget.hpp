#pragma once
#include <QtWidgets>
#include "Piece.hpp"

namespace Vue
{
    enum class TypePiece
    {
        Pion,
        Fou,
        Roi,
        Tour
    };
    enum class Mode
    {
        Placer,
        Effacer
    };

    class SideWidget : public QWidget
    {
        Q_OBJECT

    public:
        SideWidget(QWidget *parent = nullptr) : QWidget(parent)
        {
            QVBoxLayout *layout = new QVBoxLayout(this);

            // --- LABEL SELECTION ---
            selectionLabel_ = new QLabel("Sélection: Pion Blanc");
            layout->addWidget(selectionLabel_);
            selectionLabel_->setAlignment(Qt::AlignCenter);
            modeLabel_ = new QLabel("Mode: Placer");
            layout->addWidget(modeLabel_);
            modeLabel_->setAlignment(Qt::AlignCenter);

            layout->addSpacing(10);

            // --- SECTION PIECES ---
            layout->addWidget(new QLabel("Pièce"));

            pionBtn_ = new QPushButton("Pion");
            fouBtn_ = new QPushButton("Fou");
            roiBtn_ = new QPushButton("Roi");
            tourBtn_ = new QPushButton("Tour");

            layout->addWidget(pionBtn_);
            layout->addWidget(fouBtn_);
            layout->addWidget(roiBtn_);
            layout->addWidget(tourBtn_);

            layout->addSpacing(15);

            // --- SECTION COULEUR ---
            layout->addWidget(new QLabel("Couleur"));

            blancBtn_ = new QPushButton("Blanc");
            noirBtn_ = new QPushButton("Noir");

            layout->addWidget(blancBtn_);
            layout->addWidget(noirBtn_);

            layout->addStretch();
            layout->addSpacing(15);
            layout->addWidget(new QLabel("Mode"));
            placerBtn_ = new QPushButton("Placer");
            effacerBtn_ = new QPushButton("Effacer");
            layout->addWidget(effacerBtn_);
            layout->addWidget(placerBtn_);
            layout->addSpacing(30);
            layout->addWidget(new QLabel("Actions"));
            resetBtn_ = new QPushButton("Reset");

            lancerBtn_ = new QPushButton("Lancer");
            layout->addWidget(lancerBtn_);
            layout->addWidget(resetBtn_);

            // --- CONNECTIONS PIECES ---
            connect(pionBtn_, &QPushButton::clicked, this, [this]()
                    {
                pieceCourante_ = TypePiece::Pion;
                notifierChangement(); });

            connect(fouBtn_, &QPushButton::clicked, this, [this]()
                    {
                pieceCourante_ = TypePiece::Fou;
                notifierChangement(); });

            connect(roiBtn_, &QPushButton::clicked, this, [this]()
                    {
                pieceCourante_ = TypePiece::Roi;
                notifierChangement(); });

            connect(tourBtn_, &QPushButton::clicked, this, [this]()
                    {
                pieceCourante_ = TypePiece::Tour;
                notifierChangement(); });

            // --- CONNECTIONS COULEUR ---
            connect(blancBtn_, &QPushButton::clicked, this, [this]()
                    {
                couleurCourante_ = Modele::Couleur::Blanc;
                notifierChangement(); });

            connect(noirBtn_, &QPushButton::clicked, this, [this]()
                    {
                couleurCourante_ = Modele::Couleur::Noir;
                notifierChangement(); });

            // --- CONNECTIONS MODE ---
            connect(placerBtn_, &QPushButton::clicked, this, [this]()
                    {
                modeCourant_ = Mode::Placer;
                notifierChangement(); });
            connect(effacerBtn_, &QPushButton::clicked, this, [this]()
                    {
                modeCourant_ = Mode::Effacer;
                notifierChangement(); });

            connect(lancerBtn_, &QPushButton::clicked, this, [this]()
                    {
                Desactiver();
                resetButtonStyles();
                notifierActionLancer(); });

            connect(resetBtn_, &QPushButton::clicked, this, [this]()
                    {
                Activer();
                mettreAJourButtonLabel();
                mettreAJourLabel();
                notifierActionReset(); });
            connect(effacerBtn_, &QPushButton::clicked, this, [this]()
                    { notifierActionEffacer(); });
            mettreAJourButtonLabel();
        }
        bool estActif() const { return estActif_; }
        Mode modeCourant() const { return modeCourant_; }
        TypePiece pieceCourante() const { return pieceCourante_; }
        Modele::Couleur couleurCourante() const { return couleurCourante_; }
        void Desactiver()
        {
            modifierStatus(false);
            estActif_ = false;
        }
        void Activer()
        {
            modifierStatus(true);
            estActif_ = true;
        }

    signals:
        void selectionChangee(TypePiece piece, Modele::Couleur couleur);
        void actionEffacer();
        void actionLancer();
        void actionReset();

    private:
        QPushButton *pionBtn_;
        QPushButton *fouBtn_;
        QPushButton *roiBtn_;
        QPushButton *tourBtn_;
        QPushButton *blancBtn_;
        QPushButton *noirBtn_;
        QPushButton *placerBtn_;
        QPushButton *effacerBtn_;
        QPushButton *lancerBtn_;
        QPushButton *resetBtn_;
        bool estActif_ = true;
        void notifierChangement()
        {
            mettreAJourLabel();
            emit selectionChangee(pieceCourante_, couleurCourante_);
        }

        void notifierActionEffacer() { emit actionEffacer(); }
        void notifierActionLancer() { emit actionLancer(); }
        void notifierActionReset() { emit actionReset(); }

        QString pieceToString(TypePiece piece)
        {
            switch (piece)
            {
            case TypePiece::Pion:
                return "Pion";
            case TypePiece::Fou:
                return "Fou";
            case TypePiece::Roi:
                return "Roi";
            case TypePiece::Tour:
                return "Tour";
            }
            return "";
        }
        void modifierStatus(bool actif)
        {
            pionBtn_->setEnabled(actif);
            fouBtn_->setEnabled(actif);
            roiBtn_->setEnabled(actif);
            tourBtn_->setEnabled(actif);
            blancBtn_->setEnabled(actif);
            noirBtn_->setEnabled(actif);
            effacerBtn_->setEnabled(actif);
            placerBtn_->setEnabled(actif);
        }
        QString couleurToString(Modele::Couleur c)
        {
            return (c == Modele::Couleur::Blanc) ? "Blanc" : "Noir";
        }
        QString modeToString(Mode mode)
        {
            return (mode == Mode::Placer) ? "Placer" : "Effacer";
        }
        void mettreAJourButtonLabel()
        {
            updateModeButtons();
            updatePieceButtons();
            updateColorButtons();
        }
        // void mettreAJourButtonLabel()
        // {
        //     if (modeCourant_ == Mode::Placer)
        //     {
        //         placerBtn_->setStyleSheet("background-color: green;");
        //         effacerBtn_->setStyleSheet("");
        //     }
        //     else
        //     {
        //         effacerBtn_->setStyleSheet("background-color: green;");
        //         placerBtn_->setStyleSheet("");
        //     }
        //     switch (pieceCourante_)
        //     {
        //     case TypePiece::Pion:
        //         pionBtn_->setStyleSheet("background-color: green;");
        //         fouBtn_->setStyleSheet("");
        //         roiBtn_->setStyleSheet("");
        //         tourBtn_->setStyleSheet("");
        //         break;
        //     case TypePiece::Fou:
        //         fouBtn_->setStyleSheet("background-color: green;");
        //         pionBtn_->setStyleSheet("");
        //         roiBtn_->setStyleSheet("");
        //         tourBtn_->setStyleSheet("");
        //         break;
        //     case TypePiece::Roi:
        //         roiBtn_->setStyleSheet("background-color: green;");
        //         pionBtn_->setStyleSheet("");
        //         fouBtn_->setStyleSheet("");
        //         tourBtn_->setStyleSheet("");
        //         break;
        //     case TypePiece::Tour:
        //         tourBtn_->setStyleSheet("background-color: green;");
        //         pionBtn_->setStyleSheet("");
        //         fouBtn_->setStyleSheet("");
        //         roiBtn_->setStyleSheet("");
        //         break;
        //     default:
        //         break;
        //     }
        //     switch (couleurCourante_)
        //     {
        //     case Modele::Couleur::Blanc:
        //         blancBtn_->setStyleSheet("background-color: white;");
        //         noirBtn_->setStyleSheet("");
        //         break;
        //     case Modele::Couleur::Noir:
        //         noirBtn_->setStyleSheet("background-color: black;");
        //         blancBtn_->setStyleSheet("");
        //         break;
        //     default:
        //         break;
        //     }
        // }
        void setSelected(QPushButton *btn, bool selected)
        {
            btn->setStyleSheet(selected ? "background-color: #2ecc71; color: white; font-weight: bold;"
                                        : "");
        }
        void updatePieceButtons()
        {
            setSelected(pionBtn_, pieceCourante_ == TypePiece::Pion);
            setSelected(fouBtn_, pieceCourante_ == TypePiece::Fou);
            setSelected(roiBtn_, pieceCourante_ == TypePiece::Roi);
            setSelected(tourBtn_, pieceCourante_ == TypePiece::Tour);
        }
        void updateModeButtons()
        {
            setSelected(placerBtn_, modeCourant_ == Mode::Placer);
            setSelected(effacerBtn_, modeCourant_ == Mode::Effacer);
        }
        void resetButtonStyles()
        {
            placerBtn_->setStyleSheet("");
            effacerBtn_->setStyleSheet("");
            pionBtn_->setStyleSheet("");
            fouBtn_->setStyleSheet("");
            roiBtn_->setStyleSheet("");
            tourBtn_->setStyleSheet("");
            blancBtn_->setStyleSheet("");
            noirBtn_->setStyleSheet("");
            selectionLabel_->setText("Tour Blanc");
            modeLabel_->setText("");
        }
        void updateColorButtons()
        {
            blancBtn_->setStyleSheet(
                couleurCourante_ == Modele::Couleur::Blanc
                    ? "background-color: white; border: 2px solid #2ecc71; color: black; font-weight: bold;"
                    : "background-color: white; color: black;");

            noirBtn_->setStyleSheet(
                couleurCourante_ == Modele::Couleur::Noir
                    ? "background-color: black; color: white; border: 2px solid #2ecc71; font-weight: bold;"
                    : "background-color: black; color: white;");
        }
        void mettreAJourLabel()
        {
            selectionLabel_->setText(
                "Sélection: " + pieceToString(pieceCourante_) + " " + couleurToString(couleurCourante_));
            modeLabel_->setText("Mode: " + modeToString(modeCourant_));
            mettreAJourButtonLabel();
        }

        // --- DONNÉES ---
        TypePiece pieceCourante_ = TypePiece::Pion;
        Modele::Couleur couleurCourante_ = Modele::Couleur::Blanc;
        Mode modeCourant_ = Mode::Placer;
        QLabel *selectionLabel_;
        QLabel *modeLabel_;
    };
}