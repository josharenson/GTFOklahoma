#include <QSqlError>

#include "../GameEngine.h"
#include "PlayerStatsModel.h"

PlayerStatsModel::PlayerStatsModel(GameEngine *gameEngine,
                                   SqliteDbConn *dbConn,
                                   QObject *parent)
    : SqlQueryModel(dbConn, parent)
{
    connect(gameEngine, &GameEngine::currentPlayerChanged,
            this, &PlayerStatsModel::updateCurrentPlayer);

    m_baseQuery = QString("SELECT PlayerStats.* \
                           FROM PlayerStats \
                           WHERE PlayerStats.player_name='%1'");
    // FIXME
    this->updateCurrentPlayer("HACK: NOT A REAL NAME");
}

qreal PlayerStatsModel::currentValue(const QString &statName) const
{
    //TODO: It is probably worth checking that statName exists

    // If no rows are returned, the player doesn't have a value for this stat yet
    // so return 0
    QString queryStr = QString("SELECT CASE WHEN COUNT(1) > 0 \
                                THEN PlayerStats.value ELSE 0 END as value \
                                FROM PlayerStats \
                                WHERE PlayerStats.stat_name = '%1' \
                                AND PlayerStats.player_name = '%2'")
                       .arg(statName)
                       .arg(m_currentPlayer);

    QSqlQuery query = arbitraryQuery(queryStr, __func__);
    if (query.first()) {
        return query.value("value").toReal();
    } else {
        qDebug() << "Error retrieving stat " << statName;
        return 0;
    }
}

QHash<QString, qreal> PlayerStatsModel::statsForItem(const QString &itemName) const
{
    // Its kind of a hack that this method is here instead of being in its own model
    // but meh.

    QHash<QString, qreal> results;
    QString queryStr = QString("SELECT \
                                    stat_category_name, \
                                    delta \
                                FROM ItemStatModifiers \
                                WHERE ItemStatModifiers.item_name='%1'")
                        .arg(itemName);
    QSqlQuery query = arbitraryQuery(queryStr, __func__);
    while (query.next()) {
        QString statCategoryName = query.value("stat_category_name").toString();
        qreal delta = query.value("delta").toReal();

        results[statCategoryName] = delta;
    }

    return results;
}

void PlayerStatsModel::updateStat(const QString &statName, const qreal delta)
{
    qreal newValue = this->currentValue(statName) + delta;
    QString queryStr = QString("INSERT OR REPLACE INTO \
                                PlayerStats( \
                                    player_name, \
                                    stat_name, \
                                    value) \
                                VALUES('%1', '%2', '%3')")
                      .arg(m_currentPlayer)
                      .arg(statName)
                      .arg(newValue);

    QSqlQuery query = arbitraryQuery(queryStr, __func__);
    if (!query.lastError().isValid()) {
        qDebug() << "Updated " << statName << " to " << newValue;
    }
}

void PlayerStatsModel::updateCurrentPlayer(const QString &playerName)
{
    m_currentPlayer = playerName;
    this->setQuery(m_baseQuery.arg(m_currentPlayer));
}