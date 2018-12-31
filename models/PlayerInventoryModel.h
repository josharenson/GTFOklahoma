#pragma once

#include "SqliteDbConn.h"
#include "SqlQueryModel.h"

class GameEngine;
class PlayerInventoryModel : public SqlQueryModel
{
    Q_OBJECT

public:
    explicit PlayerInventoryModel(GameEngine *gameEngine,
                                  SqliteDbConn *dbConn,
                                  QObject *parent=nullptr);

    bool addItemToInventory(const QString &itemName);
    bool playerCanAddItem(const QString &itemName) const;
    qreal inventoryWeightKg() const;

signals:
    void currentPlayerChanged();

private:
    bool playerHasItem(const QString &itemName) const;
    bool playerHasItemCategory(const QString &itemName) const;

    void updateCurrentPlayer(const QString &playerName);
    QString m_currentPlayer;

    QString m_baseQuery;
};
