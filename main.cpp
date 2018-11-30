#include "MainWindow.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
