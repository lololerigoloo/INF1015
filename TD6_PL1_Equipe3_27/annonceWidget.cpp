#include "annonceWidget.hpp"

QString Vue::AnnonceWidget::transformerCouleurEnTexte(const Modele::Couleur &couleur)
{
    QString texte;
    switch (couleur)
    {
    case Modele::Couleur::Blanc:
        texte = "Blanc";
        break;
    case Modele::Couleur::Noir:
        texte = "Noir";
        break;
    default:
        texte = "Inconnu";
        break;
    }
    return texte;
}

Vue::AnnonceWidget::AnnonceWidget(QWidget *parent) : QWidget(parent)
{

    label_ = new QLabel("Bienvenue dans le jeu d'échecs !", this);
    labelTour_ = new QLabel("*u*   *u*   *u*", this);
    label_->setAlignment(Qt::AlignCenter);
    labelTour_->setAlignment(Qt::AlignCenter);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);
    layout->addWidget(labelTour_);
    layout->addWidget(label_);

    setStyleSheet("background-color: brown; color: white;");
    setFixedHeight(120); 
}
void Vue::AnnonceWidget::mettreAJourAnnonce(const Modele::BlocInformation &info)
{
    QString texte = QString("C'est au tour des %1").arg(transformerCouleurEnTexte(info.estTourBlanc ? Modele::Couleur::Blanc : Modele::Couleur::Noir));
    labelTour_->setText(texte);

    if (info.estEchecEtMat)
    {
        label_->setText("Échec et Mat ! Fin de la partie. les " + transformerCouleurEnTexte(info.estTourBlanc ? Modele::Couleur::Noir : Modele::Couleur::Blanc) + " gagnent !");
        emit EchecEtMat(info.estTourBlanc ? Modele::Couleur::Noir : Modele::Couleur::Blanc);
    }
    else if (info.estEchec)
    {
        label_->setText(" les " + transformerCouleurEnTexte(info.estTourBlanc ? Modele::Couleur::Blanc : Modele::Couleur::Noir) + " sont en échec !");
    }
    else
    {
        label_->setText("");
    }
    if (info.estTourBlanc)
    {
        labelTour_->setText("C'est au tour des Blancs");
    }
    else
    {
        labelTour_->setText("C'est au tour des Noirs");
    }
    
}