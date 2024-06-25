QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    FileTypeSizeStrategy.cpp \
    FolderSizeStrategy.cpp

HEADERS += \
    Context.h \
    FileTypeSizeStrategy.h \
    FolderSizeStrategy.h \
    ICalculationStrategy.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
