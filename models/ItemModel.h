#pragma once

#include "SqliteDbConn.h"
#include "SqlQueryModel.h"

class GameEngine;
class ItemModel : public SqlQueryModel
{
    Q_OBJECT

public:
    ItemModel(GameEngine *gameEngine,
              SqliteDbConn *dbConn,
              QObject *parent=nullptr);

private:
    QString m_baseQuery;
};
