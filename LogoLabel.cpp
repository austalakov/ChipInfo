#include "LogoLabel.h"
#include <QDesktopServices>
#include <QUrl>

LogoLabel::LogoLabel(QString text, QString url, QWidget *parent) :
    QLabel(parent)
{
    //setPixmap(QPixmap("://resources/LOGO.png").scaledToWidth(75));
    setText(text);
    setCursor(Qt::PointingHandCursor);
    myUrl = url;
}

void LogoLabel::mousePressEvent( QMouseEvent * event )
{
    QDesktopServices::openUrl(QUrl(myUrl));
}
