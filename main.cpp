#include <QDebug>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QUrl>

#include "GameEngine.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine qmlEngine;
    GameEngine gameEngine(qmlEngine);

    qmlEngine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    return app.exec();
}
