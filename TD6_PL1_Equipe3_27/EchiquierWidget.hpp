#pragma once
#include <QWidget>

namespace Vue {

class EchiquierWidget : public QWidget {
    Q_OBJECT
public:
    EchiquierWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    static const int N_CASES = 8;
    int tailleCase_;
};

}