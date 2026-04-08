#pragma once
#include <QPixmap>
#include <QMap>
#include <QString>
#include <QDebug>

namespace Vue
{
    class PiecePixmapManager
    {
    public:
        static PiecePixmapManager &instance()
        {
            static PiecePixmapManager inst;
            return inst;
        }

        const QPixmap &getPixmap(const QString &pieceName) const
        {
            auto it = pixmaps_.find(pieceName);
            if (it != pixmaps_.end())
                return it.value(); 
            return fallback_;      
        }

        void setTailleCase(int taille) { tailleCase_ = taille; }

    private:
        PiecePixmapManager() { chargerToutes(); }

        void chargerToutes()
        {
            // Toutes les pièces blanches
            charger("pionBlanc", ":/images/pionBlanc.png");
            charger("fouBlanc", ":/images/fouBlanc.png");
            charger("roiBlanc", ":/images/roiBlanc.png");

            // Toutes les pièces noires
            charger("pionNoir", ":/images/pionNoir.png");
            charger("fouNoir", ":/images/fouNoir.png");
            charger("roiNoir", ":/images/roiNoir.png");
        }

        void charger(const QString &nom, const QString &chemin)
        {
            QPixmap px(chemin);
            if (px.isNull())
                qDebug() << "Image manquante :" << chemin;
            else
                pixmaps_[nom] = px.scaled(tailleCase_, tailleCase_,
                                          Qt::KeepAspectRatio,
                                          Qt::SmoothTransformation);
        }

        QMap<QString, QPixmap> pixmaps_;
        QPixmap fallback_; // image vide si pièce introuvable
        int tailleCase_ = 80;
    };
}