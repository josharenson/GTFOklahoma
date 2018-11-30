#pragma once

#include <QHash>
#include <QModelIndex>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QVariant>

#include "SqliteDbConn.h"

class SqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit SqlQueryModel(SqliteDbConn *dbConn, QObject *parent = 0);
    ~SqlQueryModel();

    void setQuery(const QString &query);
    void setQuery(const QSqlQuery &query);
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const {	return m_roleNames;	}

private:
    void generateRoleNames();
    QHash<int, QByteArray> m_roleNames;

protected:
    SqliteDbConn *m_dbConn;
};
