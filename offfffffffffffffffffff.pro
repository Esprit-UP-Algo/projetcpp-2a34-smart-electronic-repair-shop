QT += core gui sql network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = projet_reparation
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    reparation.cpp \
    connection.cpp

HEADERS += \
    mainwindow.h \
    reparation.h \
    connection.h

FORMS += \
    mainwindow.ui

# Pour la sérialisation JSON (nécessaire pour TextBelt)
QT += network
