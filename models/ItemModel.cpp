#include "../GameEngine.h"
#include "ItemModel.h"

ItemModel::ItemModel(GameEngine *gameEngine,
                     SqliteDbConn *dbConn,
                     QObject *parent)
    : SqlQueryModel(dbConn, parent)
{
    Q_UNUSED(gameEngine);
}
