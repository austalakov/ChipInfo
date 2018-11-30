#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include "ChipDetails.h"
#include "ChipDetailsWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSize sizeHint() const;

private slots:
    void searchTextChanged(QString text);
    void listItemClicked(QListWidgetItem *);
    void listItemSelected();
    void searchReturnPressed();
    void markComboChanged(QString);
    
private:
    void setupUi();
    void parseFiles(QStringList files);

    QHash<QString, QList<ChipDetails>> allChips;
    QComboBox *markCombo;
    QListWidget *chipList;
    QLineEdit *searchEdit;
    QLabel *numberLabel;
    ChipDetailsWidget *detailsWidget;
};

#endif // MAINWINDOW_H
