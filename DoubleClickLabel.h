#ifndef DOUBLECLICKLABEL_H
#define DOUBLECLICKLABEL_H

#include <QLabel>

class DoubleClickLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DoubleClickLabel(QWidget *parent = 0);
    
signals:
    void doubleClicked();
    
public slots:

protected:
    void mouseDoubleClickEvent ( QMouseEvent * event );
    
};

#endif // DOUBLECLICKLABEL_H
