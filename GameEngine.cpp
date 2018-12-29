#include "GameEngine.h"

#include <QDebug>
#include <QObject>
#include <QQmlContext>
#include <QSqlError>

GameEngine::GameEngine(const QQmlApplicationEngine &qmlEngine, QObject *parent)
    : QObject(parent),
      m_dbConn { new SqliteDbConn(DB_PATH) },
      m_eventTimer { new QTimer(this) },
      m_playerInventoryModel { new PlayerInventoryModel(this, m_dbConn, parent) },
      m_playerStatsModel { new PlayerStatsModel(this, m_dbConn, parent) },
      m_storeModel { new StoreModel(m_dbConn, parent) }
{
    qmlEngine.rootContext()->setContextProperty("GameEngine", this);
    qmlEngine.rootContext()->setContextProperty("PlayerInventoryModel", m_playerInventoryModel);
    qmlEngine.rootContext()->setContextProperty("PlayerStatsModel", m_playerStatsModel);
    qmlEngine.rootContext()->setContextProperty("StoreModel", m_storeModel);

    connect(m_eventTimer, SIGNAL(timeout()), this, SLOT(tick()));
    connect(this, SIGNAL(eventTimerRunningChanged()), this, SLOT(toggleEventTimer()));
}

GameEngine::~GameEngine()
{
    delete(m_dbConn);
    delete(m_eventTimer);
    delete(m_playerInventoryModel);
    delete(m_playerStatsModel);
    delete(m_storeModel);
}

void GameEngine::addItemToInventory(const QString &itemName)
{
   if(m_playerInventoryModel->addItemToInventory(itemName)) {
        QHash<QString, qreal> itemStats = m_playerStatsModel->statsForItem(itemName);
        foreach (const auto &key, itemStats.keys()) {
            m_playerStatsModel->updateStat(key, itemStats[key]);
        }
   }
}

QString GameEngine::currentPlayer() const
{
    return m_currentPlayer;
}

void GameEngine::setCurrentPlayer(const QString &playerName)
{
    if (playerName != m_currentPlayer) {
        m_currentPlayer = playerName;
        currentPlayerChanged(m_currentPlayer);
    }
}

void GameEngine::tick() const
{
    qDebug() << "TICK";
}

void GameEngine::toggleEventTimer()
{
    if (m_eventTimerRunning) {
        m_eventTimer->start(TICK_INTERVAL_MS);
    } else {
        m_eventTimer->stop();
    }
}

