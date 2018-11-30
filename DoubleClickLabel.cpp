#include "DoubleClickLabel.h"

DoubleClickLabel::DoubleClickLabel(QWidget *parent) :
    QLabel(parent)
{
}

void DoubleClickLabel::mouseDoubleClickEvent ( QMouseEvent * event )
{
    emit doubleClicked();
}
