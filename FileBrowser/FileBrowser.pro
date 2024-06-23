QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    FileSizeCalculator.cpp \
    FileTypeSizeCalculator.cpp

HEADERS += \
    FileSizeCalculator.h \
    FileTypeSizeCalculator.h \
    ISizeCalculator.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
