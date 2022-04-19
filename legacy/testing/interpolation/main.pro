TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

INCLUDEPATH += \
    ../../Hitme.ui/signal/processor

SOURCES += \
        main.cpp \
    ../../Hitme.ui/signal/processor/cinterpolation.cpp

HEADERS += \
    ../../Hitme.ui/signal/processor/cinterpolation.h
