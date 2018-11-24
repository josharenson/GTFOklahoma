TEMPLATE = app

QT += core qml quick sql
CONFIG += c++14

INCLUDEPATH += /usr/local/include/

# HEADERS += plugins/engine.h \

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

