#include "MainWindow.h"
#include <QGridLayout>
#include <QRegExp>
#include <QDebug>
#include <QSplitter>
#include "BasicExcel.hpp"
#include "ChipDetailsWidget.h"
#include "LogoLabel.h"

using namespace YExcel;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi();
    setWindowTitle(tr("Chip Info"));

    QStringList files;
    files << "ATI.xls" << "NVIDIA.xls";
    parseFiles(files);
}

QSize MainWindow::sizeHint() const
{
    return QSize(600, 600);
}

void MainWindow::setupUi()
{
    QLabel *searchLabel = new QLabel(tr("Search"), this);
    searchEdit = new QLineEdit(this);
    chipList = new QListWidget(this);
    chipList->setSelectionMode(QAbstractItemView::SingleSelection);
    QLabel *totalLabel = new QLabel(tr("Total"), this);
    numberLabel = new QLabel("0");
    detailsWidget = new ChipDetailsWidget(this);
    markCombo = new QComboBox(this);

    connect(searchEdit, SIGNAL(textChanged(QString)), this, SLOT(searchTextChanged(QString)));
    connect(searchEdit, SIGNAL(returnPressed()), this, SLOT(searchReturnPressed()));
    connect(chipList, SIGNAL(itemSelectionChanged()), this, SLOT(listItemSelected()));
    connect(markCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(markComboChanged(QString)));
    //connect(chipList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listItemClicked(QListWidgetItem*)));

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(searchLabel, 0, 0);
    grid->addWidget(searchEdit, 0, 1);
    grid->addWidget(markCombo, 1, 0, 1, 2);
    grid->addWidget(chipList, 2, 0, 1, 2);
    grid->addWidget(totalLabel, 3, 0);
    grid->addWidget(numberLabel, 3, 1, 1, 1, Qt::AlignRight);
    grid->setRowStretch(2, 1);
    grid->setColumnStretch(1, 1);

    QWidget *left = new QWidget(this);
    left->setLayout(grid);

    LogoLabel *notebookLabel = new LogoLabel("<b><i><h2>notebook1.ru</h2></i></b>", "www.notebook1.ru", this);
    LogoLabel *notebookBgLabel = new LogoLabel("<b><i><h2>notebookbg.com</h2></i></b>", "www.notebookbg.com", this);
    LogoLabel *logo = new LogoLabel("", "http://www.kae2012.com/", this);
    logo->setPixmap(QPixmap("://resources/LOGO.png").scaledToWidth(50));

    QGridLayout *grid1 = new QGridLayout;
    grid1->addWidget(detailsWidget, 0, 0, 1, 3);
    grid1->addWidget(notebookLabel, 1, 0, 1, 1, Qt::AlignLeft | Qt::AlignBottom);
    grid1->addWidget(notebookBgLabel, 2, 0, 1, 1, Qt::AlignCenter | Qt::AlignBottom);
    grid1->addWidget(logo, 1, 1, 2, 1, Qt::AlignRight | Qt::AlignBottom);
    grid1->setRowStretch(0, 1);
    grid1->setColumnStretch(1, 1);

    QWidget *right = new QWidget(this);
    right->setLayout(grid1);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setSizes(QList<int>() << 30 << 70);
    splitter->setStretchFactor(1, 1);
    splitter->setStretchFactor(0, 1);
    splitter->addWidget(left);
    splitter->addWidget(right);

    this->setCentralWidget(splitter);
}

void MainWindow::parseFiles(QStringList files)
{
    BasicExcel e;
    foreach(QString file, files)
    {
        QString markName = file.split('.').first();
        markCombo->addItem(markName);

        QList<ChipDetails> chips;

        e.Load(file.toUtf8().data());
        BasicExcelWorksheet* sheet1 = e.GetWorksheet("Sheet1");
        cout << file.toUtf8().data();
        if (sheet1)
        {
            size_t maxRows = sheet1->GetTotalRows();
            size_t maxCols = sheet1->GetTotalCols();
            cout << "Dimension of " << sheet1->GetAnsiSheetName() <<
                " (" << maxRows << ", " << maxCols << ")" << endl;

            QStringList headers;

            for (size_t r=0; r<maxRows; ++r)
            {
                QList<QPair<QString, QString>> details;
                QString marking;

                printf("%10d ", r+1);
                for (size_t c=0; c<maxCols; ++c)
                {
                    BasicExcelCell* cell = sheet1->Cell(r,c);
                    QString value;
                    switch (cell->Type())
                    {
                      case BasicExcelCell::UNDEFINED:
                        printf(" ");
                        break;

                      case BasicExcelCell::INT:
                        printf("%10d", cell->GetInteger());
                        value = QString::number(cell->GetInteger());
                        break;

                      case BasicExcelCell::DOUBLE:
                        printf("%10.6lf", cell->GetDouble());
                        value = QString::number(cell->GetDouble());
                        break;

                      case BasicExcelCell::STRING:
                        printf("%10s", cell->GetString());
                        value = cell->GetString();
                        break;

                      case BasicExcelCell::WSTRING:
                        wprintf(L"%10s", cell->GetWString());
                        value = QString::fromWCharArray(cell->GetWString());
                        break;
                    }

                    value = value.trimmed();

                    if(r == 0)
                    {
                        headers.append(value);
                    }
                    else
                    {
                        details.append(QPair<QString, QString>(headers.at(c), value));
                        if(c == 0)
                            marking = value;
                    }

                }
                cout << endl;

                if(r != 0 && !marking.isEmpty())
                    chips.append(ChipDetails(marking, details));
            }
        }
        cout << endl;
        allChips.insert(markName, chips);
    }

    markCombo->setCurrentIndex(1);
}

void MainWindow::searchTextChanged(QString text)
{
    chipList->clear();
    if(allChips.keys().contains(markCombo->currentText()))
    {
        foreach(ChipDetails chip, allChips.value(markCombo->currentText()))
        {
            if(chip.contains(text))
            {
                QListWidgetItem *item = new QListWidgetItem(chip.marking());
                item->setData(Qt::UserRole, QVariant::fromValue(chip));
                chipList->addItem(item);
            }
        }
    }

    numberLabel->setText(QString::number(chipList->count()));
}

void MainWindow::listItemClicked(QListWidgetItem *item)
{
    detailsWidget->setData(item->data(Qt::UserRole).value<ChipDetails>());
}

void MainWindow::listItemSelected()
{
    if(!chipList->selectedItems().isEmpty())
    {
        detailsWidget->setData(chipList->selectedItems().first()->data(Qt::UserRole).value<ChipDetails>());
    }
}

void MainWindow::searchReturnPressed()
{
    searchTextChanged(searchEdit->text());
    if(chipList->count() > 0)
        detailsWidget->setData(chipList->item(0)->data(Qt::UserRole).value<ChipDetails>());
}

void MainWindow::markComboChanged(QString current)
{
    chipList->clear();
    if(!allChips.isEmpty())
    {
        foreach(ChipDetails chip, allChips.value(current))
        {
            QListWidgetItem *item = new QListWidgetItem(chip.marking());
            item->setData(Qt::UserRole, QVariant::fromValue(chip));
            chipList->addItem(item);
        }
    }
    numberLabel->setText(QString::number(chipList->count()));
}

MainWindow::~MainWindow()
{

}
