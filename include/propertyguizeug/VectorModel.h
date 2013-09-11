
#pragma once

#include <QAbstractTableModel>
#include <propertyzeug/Property.h>
#include "propertyguizeug.h"

namespace propertyguizeug {

using namespace propertyzeug;

template <typename Type>
class VectorModel : public QAbstractTableModel
{
public:
    VectorModel(Property<std::vector<Type>> * property, QObject * parent = nullptr);
    virtual ~VectorModel();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

protected:
    Property<std::vector<Type>> * m_property;

};

template <typename Type>
VectorModel<Type>::VectorModel(Property<std::vector<Type>> * property, QObject * parent)
:   QAbstractTableModel(parent)
,   m_property(property)
{
}

template <typename Type>
VectorModel<Type>::~VectorModel()
{
}

template <typename Type>
int VectorModel<Type>::rowCount(const QModelIndex & parent) const
{
    return m_property->rows();
}

template <typename Type>
int VectorModel<Type>::columnCount(const QModelIndex & parent) const
{
    return m_property->columns();
}

template <typename Type>
QVariant VectorModel<Type>::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole) {
        Type data = m_property->value().at(m_property->columns() * index.row() + index.column());
        return QVariant(data);
    }

    return QVariant();
}

template <typename Type>
QVariant VectorModel<Type>::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

template <typename Type>
Qt::ItemFlags VectorModel<Type>::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

} // namespace
