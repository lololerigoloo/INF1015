#pragma once
#include <QMainWindow>
#include "EchiquierWidget.hpp"
#include <memory>
#include "Echiquier.hpp"
#include <QPixmap>
#include <QLabel>

namespace Vue
{
    class MainWinUi : public QMainWindow
    {
        Q_OBJECT
    public:
        MainWinUi();
        void mousePressEvent(QMouseEvent *event) override;

    private:
        std::shared_ptr<Modele::Echiquier> echiquier_;
        std::unique_ptr<Vue::EchiquierWidget> echiquierWidget_;
    };
}