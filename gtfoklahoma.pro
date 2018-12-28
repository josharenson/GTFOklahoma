TEMPLATE = app

QT += core qml quick sql
CONFIG += c++14

INCLUDEPATH += /usr/local/include/

HEADERS += GameEngine.h \
           models/ItemModel.h \
           models/PlayerInventoryModel.h \
           models/PlayerStatsModel.h \
           models/SqliteDbConn.h \
           models/SqlQueryModel.h \
           models/StoreModel.h

SOURCES += main.cpp \
           GameEngine.cpp \
           models/ItemModel.cpp \
           models/PlayerInventoryModel.cpp \
           models/PlayerStatsModel.cpp \
           models/SqliteDbConn.cpp \
           models/SqlQueryModel.cpp \
           models/StoreModel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
# include(deployment.pri)

