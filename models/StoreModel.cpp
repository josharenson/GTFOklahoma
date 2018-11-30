#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

#include "StoreModel.h"

StoreModel::StoreModel(SqliteDbConn *dbConn, QObject *parent)
    : SqlQueryModel(dbConn, parent)
{
    connect(this, &StoreModel::storeNameChanged,
            this, &StoreModel::updateCategories);

    m_baseQuery = QString("SELECT Items.* FROM Items, Stores, StoreCategories \
                           ON StoreCategories.store_name = Stores.name \
                           WHERE Stores.name = '%1' \
                           AND StoreCategories.category_name == Items.category ");

    /*
     * [HACK] I think this needs to happen so that role names are generated before the model
     * is actually used
     */
    this->setStoreName("HACK: NOT A REAL STORE NAME");
}

QString StoreModel::currentCategory() const
{
    return m_currentCategory;
}

void StoreModel::setCurrentCategory(const QString &categoryName)
{
    if (categoryName != m_currentCategory) {
        m_currentCategory = categoryName;

        QString baseQuery = m_baseQuery.arg(m_storeName);
        QString filterQuery = QString("AND Items.category = '%1'")
                              .arg(categoryName);
        this->setQuery(baseQuery + filterQuery);

        currentCategoryChanged();
    }
}

QString StoreModel::storeName() const
{
    return m_storeName;
}

void StoreModel::setStoreName(const QString &storeName)
{
    if (m_storeName != storeName) {
        m_storeName = storeName;

        this->setQuery(m_baseQuery.arg(m_storeName));
        emit storeNameChanged();
    }
}

void StoreModel::updateCategories()
{
    QString queryStr = QString("SELECT category_name FROM StoreCategories \
                                WHERE store_name = '%1'")
                       .arg(m_storeName);

    QSqlQuery query(queryStr, m_dbConn->db());
    while (query.next()) {
        QString category = query.value(0).toString();
        m_categories << category;
    }

    if (!m_categories.isEmpty()) {
        this->setCurrentCategory(m_categories.first());
    }

    emit categoriesChanged();
}
