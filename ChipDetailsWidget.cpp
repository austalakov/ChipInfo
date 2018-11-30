#include "ChipDetailsWidget.h"
#include "imageviewer.h"
#include "DoubleClickLabel.h"

#include <QLineEdit>
#include <QFormLayout>
#include <QFile>
#include <QDebug>
#include <QTextEdit>
#include <QPushButton>
#include <QCoreApplication>

ChipDetailsWidget::ChipDetailsWidget(ChipDetails chip, QWidget *parent) :
    QWidget(parent)
{
    setData(chip);
    setMinimumWidth(400);
}

ChipDetailsWidget::ChipDetailsWidget(QWidget *parent) :
    QWidget(parent)
{
    setMinimumWidth(400);
}

void ChipDetailsWidget::setData(ChipDetails chip)
{
    current = chip;

    if(layout() != NULL)
    {
        QLayoutItem* item;
        while ( ( item = layout()->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
        delete layout();
    }

    QFormLayout *form = new QFormLayout(this);
    for(int i = 0; i < chip.attributes().count(); ++i)
    {
        if(i == chip.attributes().count() - 1)
        {
            QTextEdit *lastEdit = new QTextEdit(chip.attributes().at(i).second, this);
            lastEdit->setReadOnly(true);
            /*QPushButton *lastButton = new QPushButton(">>", this);
            QHBoxLayout *hbox = new QHBoxLayout;
            hbox->addWidget(lastEdit, 1);
            hbox->addWidget(lastButton, 0);
            hbox->setContentsMargins(0, 0, 0, 0);

            QWidget *lastWidget = new QWidget(this);
            lastWidget->setLayout(hbox);*/
            form->addRow(chip.attributes().at(i).first, lastEdit);
        }
        else
        {
            QLineEdit *valueEdit = new QLineEdit(chip.attributes().at(i).second);
            valueEdit->setReadOnly(true);
            form->addRow(chip.attributes().at(i).first, valueEdit);
        }
    }
    QString fileName = QCoreApplication::applicationDirPath() + "\\resources\\snimki\\" + chip.marking() + ".JPG";
    QImage image(fileName);
    if (!image.isNull())
    {
        DoubleClickLabel *imageLabel = new DoubleClickLabel(this);
        form->addRow(imageLabel);
        connect(imageLabel, SIGNAL(doubleClicked()), this, SLOT(labelDoubleClicked()));
        imageLabel->setPixmap(QPixmap::fromImage(image).scaledToWidth(300));
    }


    /*QPixmap pix = QPixmap("://resources/snimki/" + chip.marking() + ".JPG");
    if(!pix.isNull())
    {
        DoubleClickLabel *imageLabel = new DoubleClickLabel(this);
        imageLabel->setPixmap(pix.scaledToWidth(300));
        form->addRow(imageLabel);
        connect(imageLabel, SIGNAL(doubleClicked()), this, SLOT(labelDoubleClicked()));
    }*/

    setLayout(form);
}

void ChipDetailsWidget::labelDoubleClicked()
{
    ImageViewer iv(current.marking(), this);
    iv.exec();
}
