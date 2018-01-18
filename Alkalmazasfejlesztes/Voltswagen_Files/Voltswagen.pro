#-------------------------------------------------
#
# Project created by QtCreator 2017-11-20T18:07:02
#
#-------------------------------------------------
CONFIG += c++14
QMAKE_CXXFLAGS_CXX11    = -std=c++1y


QT += qml quick widgets
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quit_2017_hazi
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    MainWindowsEventHandling.cpp \
    RobotProxy.cpp \
    RobotState.cpp \
    RobotStateHistory.cpp \
    main.cpp \
    StvApplication.cpp \
    Communication/Communication.cpp \
    Communication/CommunicationSerialPort.cpp

HEADERS += \
    MainWindowsEventHandling.h \
    RobotProxy.h \
    RobotState.h \
    RobotStateHistory.h \
    StvApplication.h \
    Communication/Communication.h \
    Communication/CommunicationSerialPort.h

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH

RESOURCES += qml.qrc

