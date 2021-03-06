#include "SqlQueryModel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlField>
#include <QSqlRecord>

SqlQueryModel::SqlQueryModel(SqliteDbConn *dbConn, QObject *parent)
    : QSqlQueryModel(parent)
{
    m_dbConn = dbConn;
}

SqlQueryModel::~SqlQueryModel()
{
    delete(m_dbConn);
}

QSqlQuery SqlQueryModel::arbitraryQuery(const QString &queryStr, const QString &caller) const
{
    QSqlQuery query(m_dbConn->db());
    if (!query.prepare(queryStr)) {
        qDebug() << "Error preparing query for " << caller;
        qDebug() << query.lastError().text();
    }

    if(!query.exec()) {
        qDebug() << "Error executing query for " << caller;
        qDebug() << query.lastError().text();
    }

    return query;
}

void SqlQueryModel::setQuery(const QString &query)
{
    QSqlQueryModel::setQuery(query, m_dbConn->db());
    generateRoleNames();
}

void SqlQueryModel::generateRoleNames()
{
    m_roleNames.clear();
    for( int i = 0; i < record().count(); i ++) {
        m_roleNames.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
    }
}

QVariant SqlQueryModel::data(const QModelIndex &index, int role) const
{
    QVariant value;

    if(role < Qt::UserRole) {
        value = QSqlQueryModel::data(index, role);
    }
    else {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }

    return value;
}
