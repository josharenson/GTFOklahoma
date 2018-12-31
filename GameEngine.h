#pragma once

#include <QQmlApplicationEngine>
#include <QString>
#include <QTimer>

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

    Q_PROPERTY(bool eventTimerRunning
               MEMBER m_eventTimerRunning
               NOTIFY eventTimerRunningChanged)

public:
    explicit GameEngine(const QQmlApplicationEngine &qmlEngine,
                        QObject *parent=nullptr);
    ~GameEngine();

    Q_INVOKABLE void addItemToInventory(const QString &itemName);

    QString currentPlayer() const;
    void setCurrentPlayer(const QString &playerName);

    qreal kms_per_tick() const;

public slots:
    void tick() const;
    void toggleEventTimer();

signals:
    void currentPlayerChanged(const QString &playerName);
    void eventTimerRunningChanged();

private:
    const QString DB_PATH { QStringLiteral("models/gtfoklahoma.db") };

    // A reasonably fit person of average weight on a 1kg bike
    // NOTE: Bike + gear weight have a minimal effect on how fast a ride can go
    const int MAX_VELOCITY_KMH = 35;

    const int TICKS_PER_DAY = 96;
    const int TICK_INTERVAL_MS = 2000;

    // I wouldn't mess with this
    const float VELOCITY_CONSTANT = 4.5;

    QString m_currentPlayer;
    bool m_eventTimerRunning = false;
    SqliteDbConn *m_dbConn;
    QTimer *m_eventTimer;
    PlayerInventoryModel *m_playerInventoryModel;
    bool m_playerMoving = true;
    PlayerStatsModel *m_playerStatsModel;
    StoreModel *m_storeModel;
};
