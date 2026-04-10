#include "SideWidget.hpp"
void Vue::SideWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    mettreAJourButtonLabel();
}