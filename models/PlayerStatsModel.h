#pragma once

#include <QHash>
#include <QString>

#include "SqliteDbConn.h"
#include "SqlQueryModel.h"

class GameEngine;
class PlayerStatsModel : public SqlQueryModel
{
    Q_OBJECT

public:
    explicit PlayerStatsModel(GameEngine *gameEngine,
                              SqliteDbConn *dbConn,
                              QObject *parent=nullptr);

    qreal currentValue(const QString &statName) const;
    QHash<QString, qreal> statsForItem(const QString &itemName) const;
    void updateStat(const QString &statName, const qreal delta);
private:
    QString m_baseQuery;

    void updateCurrentPlayer(const QString &playerName);
    QString m_currentPlayer;
};
