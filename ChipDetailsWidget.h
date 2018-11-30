#ifndef CHIPDETAILSWIDGET_H
#define CHIPDETAILSWIDGET_H

#include <QLabel>
#include "ChipDetails.h"

class ChipDetailsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChipDetailsWidget(QWidget *parent = 0);
    explicit ChipDetailsWidget(ChipDetails chip, QWidget *parent = 0);

    void setData(ChipDetails chip);
    
signals:
    
private slots:
    void labelDoubleClicked();

private:
    ChipDetails current;
    QLabel *titleEdit;
};

#endif // CHIPDETAILSWIDGET_H
