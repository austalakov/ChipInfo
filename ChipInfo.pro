#-------------------------------------------------
#
# Project created by QtCreator 2013-08-26T10:11:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChipInfo
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ChipDetails.cpp \
    ChipDetailsWidget.cpp \
    BasicExcel.cpp \
    imageviewer.cpp \
    DoubleClickLabel.cpp \
    LogoLabel.cpp

HEADERS  += MainWindow.h \
    ChipDetails.h \
    ChipDetailsWidget.h \
    BasicExcel.hpp \
    imageviewer.h \
    DoubleClickLabel.h \
    LogoLabel.h

FORMS    +=

OTHER_FILES +=

RESOURCES += \
    ChipInfo.qrc

RC_FILE = ChipInfo.rc
