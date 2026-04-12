#pragma once
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QLabel>

namespace Vue
{
    class SelecteurDeNiveau : public QWidget
    {
        Q_OBJECT
    public:
        explicit SelecteurDeNiveau(QWidget *parent = nullptr);
        void mettreActif(bool actif);

    signals:
        void niveauSelectionne(const QString &nomNiveau);

    private slots:
        void surSelection(QListWidgetItem *item);

    private:
        QListWidget *liste_;
    };
}