#-------------------------------------------------
#
# Project created by QtCreator 2018-02-28T21:27:31
#
#-------------------------------------------------

QT       += core gui network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hitme.ui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/sources/sensor $$PWD/sources/gui $$PWD/sources/calculators


SOURCES += \
    sources/main.cpp \
    sources/gui/hitmemainwindow.cpp \
    sources/gui/caccdisplay.cpp \
    sources/sensor/cabstractdataprocessor.cpp \
    sources/sensor/csensorstatus.cpp \
    sources/sensor/cnetworksensorinterface.cpp \
    sources/sensor/csensordata.cpp \
    sources/sensor/caccdataconverter.cpp \
    sources/calculators/cabstractcalculator.cpp \
    sources/caccstorage.cpp \
    sources/sensor/csensordatareceiver.cpp \
    sources/sensor/csensorctrltransceiver.cpp

HEADERS += \
    sources/gui/hitmemainwindow.h \
    sources/gui/caccdisplay.h \
    sources/sensor/cabstractdataprocessor.h \
    sources/sensor/csensorstatus.h \
    sources/sensor/cnetworksensorinterface.h \
    sources/sensor/csensordata.h \
    sources/sensor/caccdataconverter.h \
    sources/calculators/cabstractcalculator.h \
    sources/caccstorage.h \
    sources/sensor/csensordatareceiver.h \
    sources/sensor/csensorctrltransceiver.h

FORMS += \
    forms/hitmemainwindow.ui
