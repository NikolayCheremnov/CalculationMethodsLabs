QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Lab1/lab1.cpp \
    Logger/ilogger.cpp \
    Logger/pluglogger.cpp \
    Logger/streamlogger.cpp \
    Logger/stringlogger.cpp \
    Matrix/basematrix.cpp \
    Matrix/matrixexception.cpp \
    Matrix/squarematrix.cpp \
    Matrix/triangularmatrix.cpp \
    Matrix/vector.cpp \
    main.cpp \
    gui.cpp \
    randomsystemgenerationwindow.cpp

HEADERS += \
    Lab1/lab1.h \
    Logger/ilogger.h \
    Logger/pluglogger.h \
    Logger/streamlogger.h \
    Logger/stringlogger.h \
    Matrix/basematrix.h \
    Matrix/matrixexception.h \
    Matrix/squarematrix.h \
    Matrix/triangularmatrix.h \
    Matrix/vector.h \
    gui.h \
    randomsystemgenerationwindow.h

FORMS += \
    gui.ui \
    randomsystemgenerationwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
