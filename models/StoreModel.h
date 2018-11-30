#pragma once

#include <QStringList>

#include "SqliteDbConn.h"
#include "SqlQueryModel.h"

class StoreModel : public SqlQueryModel
{
    Q_OBJECT

    Q_PROPERTY(QStringList categories MEMBER m_categories NOTIFY categoriesChanged)
    Q_PROPERTY(QString currentCategory
               READ currentCategory
               WRITE setCurrentCategory
               NOTIFY currentCategoryChanged)
    Q_PROPERTY(QString storeName READ storeName WRITE setStoreName NOTIFY storeNameChanged)

public:
    StoreModel(SqliteDbConn *dbConn, QObject *parent = 0);

    QString currentCategory() const;
    void setCurrentCategory(const QString &categoryName);

    QString storeName() const;
    void setStoreName(const QString &storeName);

signals:
    void categoriesChanged();
    void currentCategoryChanged();
    void storeNameChanged();

private:
    void updateCategories();

    QString m_baseQuery;
    QStringList m_categories;
    QString m_currentCategory;
    QString m_storeName;
};
