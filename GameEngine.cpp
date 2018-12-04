#include "GameEngine.h"

#include <QDebug>
#include <QQmlContext>
#include <QSqlError>

GameEngine::GameEngine(const QQmlApplicationEngine &qmlEngine, QObject *parent)
    : QObject(parent),
      m_dbConn { new SqliteDbConn(DB_PATH) },
      m_playerInventoryModel { new PlayerInventoryModel(this, m_dbConn, parent) },
      m_storeModel { new StoreModel(m_dbConn, parent) }
{
    qmlEngine.rootContext()->setContextProperty("GameEngine", this);
    qmlEngine.rootContext()->setContextProperty("PlayerInventoryModel", m_playerInventoryModel);
    qmlEngine.rootContext()->setContextProperty("StoreModel", m_storeModel);
}

GameEngine::~GameEngine()
{
    delete(m_dbConn);
    delete(m_playerInventoryModel);
    delete(m_storeModel);
}

void GameEngine::addItemToInventory(const QString &itemName)
{
    m_playerInventoryModel->addItemToInventory(itemName);
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
