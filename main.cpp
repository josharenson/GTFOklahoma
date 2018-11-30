#include <QDebug>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QUrl>

#include "models/SqliteDbConn.h"
#include "models/StoreModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    SqliteDbConn *dbConn = new SqliteDbConn("models/gtfoklahoma.db");
    StoreModel *storeModel = new StoreModel(dbConn);

    engine.rootContext()->setContextProperty("StoreModel", storeModel);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    return app.exec();
}
