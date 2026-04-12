#include "selecteurDeNiveau.hpp"

Vue::SelecteurDeNiveau::SelecteurDeNiveau(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(4);

    QLabel *titre = new QLabel("Fins de partie", this);
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet("color: white; font-weight: bold; font-size: 13px;");

    liste_ = new QListWidget(this);
    liste_->setStyleSheet(
        "QListWidget { background-color: #3a3a3a; color: white; border: none; }"
        "QListWidget::item { padding: 6px; border-bottom: 1px solid #555; }"
        "QListWidget::item:selected { background-color: #c0392b; }"
        "QListWidget::item:hover { background-color: #555; }"
        "QListWidget:disabled { background-color: #2a2a2a; color: #555; }"     
        "QListWidget:disabled::item:selected { background-color: #5a1a1a; }"     
    );

    liste_->addItem("Mat du couloir");
    liste_->addItem("Mat de l'escalier");
    liste_->addItem("Mat du berger");
    liste_->addItem("Mat de l'épaulette");
    liste_->addItem("Mat de Légal");
    liste_->addItem("Mat des Arabes");
    liste_->addItem("Finale Tour vs Roi");
    liste_->addItem("Finale Dame vs Roi");

    layout->addWidget(titre);
    layout->addWidget(liste_);

    connect(liste_, &QListWidget::itemClicked,
            this, &SelecteurDeNiveau::surSelection);
}

void Vue::SelecteurDeNiveau::surSelection(QListWidgetItem *item)
{
    mettreActif(false);
    emit niveauSelectionne(item->text());
}

void Vue::SelecteurDeNiveau::mettreActif(bool actif)
{
    liste_->setEnabled(actif);
    if (!actif)
        liste_->clearSelection(); 
}