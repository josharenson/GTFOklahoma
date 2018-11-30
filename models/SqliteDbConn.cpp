#include "SqliteDbConn.h"

SqliteDbConn::SqliteDbConn(const QString &dbPath, QObject *parent)
    : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    if (!m_db.isValid()) {
        qDebug() << "Could not load the QSQLITE database driver!";
    }

    m_db.setDatabaseName(dbPath);
    if (!m_db.open()) {
        qDebug() << "Could not open the database at " << dbPath;
    }
}

const QSqlDatabase SqliteDbConn::db() const
{
    return m_db;
}
