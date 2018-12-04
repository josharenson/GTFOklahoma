#include <QDebug>
#include <QSqlError>

#include "../GameEngine.h"
#include "PlayerInventoryModel.h"

PlayerInventoryModel::PlayerInventoryModel(GameEngine *gameEngine,
                                           SqliteDbConn *dbConn,
                                           QObject *parent)
    : SqlQueryModel(dbConn, parent)
{
    connect(gameEngine, &GameEngine::currentPlayerChanged,
            this, &PlayerInventoryModel::updateCurrentPlayer);

    m_baseQuery = QString("SELECT Items.* \
                           FROM Items, PlayerInventory \
                           ON Items.name=PlayerInventory.item_name \
                           WHERE PlayerInventory.player_name='%1'");

    // FIXME: This really needs to be fixed in the parent class.
    this->updateCurrentPlayer("HACK: NOT A REAL NAME");
}

void PlayerInventoryModel::addItemToInventory(const QString &itemName)
{
    qDebug() << "Trying to add " << itemName << " to " << m_currentPlayer
             << "'s inventory";

    if (!this->playerCanAddItem(itemName)) {
        return;
    }

    QString queryStr = QString("INSERT INTO \
                               PlayerInventory(item_name, player_name) \
                               VALUES('%1', '%2')")
                       .arg(itemName)
                       .arg(m_currentPlayer);

    QSqlQuery query = arbitraryQuery(queryStr, __func__);
    if (!query.lastError().isValid()) {
        qDebug() << "Successfully added " << itemName  << " to " << m_currentPlayer
                 << "'s inventory";
    }
}

bool PlayerInventoryModel::playerCanAddItem(const QString &itemName) const
{
    bool canHaveMulltiple;
    QSqlQuery query;

    /* Are multiples of this item allowed? */
    QString itemAllowsMultipleQuery = QString("SELECT Items.can_have_multiple \
                                               FROM Items \
                                               WHERE name = '%1'")
                                       .arg(itemName);

    query = arbitraryQuery(itemAllowsMultipleQuery, __func__);
    if (!query.first()) {
        qDebug() << "Item named " << itemName << " not found! Cannot add it.";
        return false;
    }

    canHaveMulltiple = query.value("can_have_multiple").toBool();
    if (this->playerHasItem(itemName) && !canHaveMulltiple) {
        qDebug() << "Not adding " << itemName << " to " << m_currentPlayer
                 << "'s inventory "
                 << "because they cannot have more than one of that item";
        return false;
    }

    /* Are multiples of this category allowed? */
    QString categoryAllowsMultiple = QString("SELECT ItemCategories.can_have_multiple \
                                              FROM Items, ItemCategories \
                                              ON Items.category=ItemCategories.name \
                                              WHERE Items.name='%1'")
                                     .arg(itemName);

    query = arbitraryQuery(categoryAllowsMultiple, __func__);
    if (!query.first()) {
        qDebug() << "Could not determine if multiple items in this category were allowed";
        return false;
    }

    canHaveMulltiple = query.value("can_have_multiple").toBool();
    if (this->playerHasItemCategory(itemName) && !canHaveMulltiple) {
        qDebug() << "Not adding " << itemName << " to " << m_currentPlayer
                 << "'s inventory "
                 << "because they cannot have more than one item in that category";
        return false;
    }

    return true;
}

bool PlayerInventoryModel::playerHasItem(const QString &itemName) const
{
    QString queryStr = QString("SELECT * FROM PlayerInventory \
                               WHERE item_name='%1' \
                               AND player_name='%2'")
                       .arg(itemName)
                       .arg(m_currentPlayer);

    QSqlQuery query = arbitraryQuery(queryStr, __func__);
    return bool(query.next());
}

bool PlayerInventoryModel::playerHasItemCategory(const QString &itemName) const
{
    QString itemCategoryQuery = QString("SELECT Items.category \
                                         FROM Items \
                                         WHERE Items.name='%1'")
                                .arg(itemName);

    QSqlQuery query = arbitraryQuery(itemCategoryQuery, __func__);
    if (!query.first()) {
        qDebug() << "Could not determine the category of a " << itemName;
        return false;
    }

    QString categoryName = query.value("category").toString();
    QString queryStr = QString("SELECT Items.category \
                                FROM Items, PlayerInventory \
                                ON PlayerInventory.item_name=Items.name \
                                WHERE Items.category='%1'")
                       .arg(categoryName);

    query = arbitraryQuery(queryStr, __func__);
    return bool(query.next());
}

void PlayerInventoryModel::updateCurrentPlayer(const QString &playerName)
{
    m_currentPlayer = playerName;
    this->setQuery(m_baseQuery.arg(m_currentPlayer));
}
