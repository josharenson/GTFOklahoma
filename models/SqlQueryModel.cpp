#include "SqlQueryModel.h"

#include <QDebug>
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

void SqlQueryModel::setQuery(const QString &query)
{
    QSqlQueryModel::setQuery(query, m_dbConn->db());
    generateRoleNames();
}

void SqlQueryModel::setQuery(const QSqlQuery & query)
{
    QSqlQueryModel::setQuery(query);
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
