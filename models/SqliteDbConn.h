# pragma once

#include <QDebug>
#include <QObject>
#include <QSqlDatabase>
#include <QString>

class SqliteDbConn : public QObject
{
    Q_OBJECT

public:
    explicit SqliteDbConn(const QString &dbPath, QObject *parent = nullptr);

    const QSqlDatabase db() const;

private:
    QSqlDatabase m_db;

};
