QT       += core gui sql charts printsupport network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appareils.cpp \
    client.cpp \
    connection.cpp \
    employe.cpp \
    main.cpp \
    mainwindow.cpp \
    pdfexporter.cpp \
    reparations.cpp \
    statistics.cpp

HEADERS += \
    appareils.h \
    client.h \
    config.h \
    connection.h \
    employe.h \
    mainwindow.h \
    pdfexporter.h \
    reparations.h \
    statistics.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
