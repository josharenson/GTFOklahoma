#pragma once

#include <QQmlApplicationEngine>
#include <QString>

#include "models/SqliteDbConn.h"
#include "models/PlayerInventoryModel.h"
#include "models/PlayerStatsModel.h"
#include "models/StoreModel.h"

class GameEngine : public QObject
{

    Q_OBJECT

    Q_PROPERTY(QString currentPlayer
               READ currentPlayer
               WRITE setCurrentPlayer
               NOTIFY currentPlayerChanged)
public:
    explicit GameEngine(const QQmlApplicationEngine &qmlEngine,
                        QObject *parent=nullptr);
    ~GameEngine();

    Q_INVOKABLE void addItemToInventory(const QString &itemName);

    QString currentPlayer() const;
    void setCurrentPlayer(const QString &playerName);

signals:
    void currentPlayerChanged(const QString &playerName);

private:
    const QString DB_PATH { QStringLiteral("models/gtfoklahoma.db") };

    QString m_currentPlayer;
    SqliteDbConn *m_dbConn;
    PlayerInventoryModel *m_playerInventoryModel;
    PlayerStatsModel *m_playerStatsModel;
    StoreModel *m_storeModel;
};
