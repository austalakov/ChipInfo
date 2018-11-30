#ifndef LOGOLABEL_H
#define LOGOLABEL_H

#include <QLabel>

class LogoLabel : public QLabel
{
    Q_OBJECT
public:
    explicit LogoLabel(QString text, QString url, QWidget *parent = 0);
    
protected:
    void mousePressEvent ( QMouseEvent * event );

private:
    QString myUrl;
    
};

#endif // LOGOLABEL_H
