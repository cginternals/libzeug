
#pragma once

#include <QAbstractItemModel>
#include "propertyguizeug.h"

namespace propertyzeug {
    template <typename Type>
    class Property;
    class PropertyGroup;
}

namespace propertyguizeug {
    
using namespace propertyzeug;

class PROPERTYGUIZEUG_API PropertyItemModel : public QAbstractItemModel
{
public:
    PropertyItemModel(PropertyGroup * root, QObject * parent = nullptr);
    virtual ~PropertyItemModel();
    
    virtual QModelIndex index(int row, int column,
                              const QModelIndex & parentIndex = QModelIndex()) const;
    
    virtual QModelIndex parent(const QModelIndex & index) const;
    
    virtual int rowCount(const QModelIndex & parentIndex = QModelIndex()) const;
    
    virtual int columnCount(const QModelIndex & parentIndex = QModelIndex()) const;
    
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;

protected:
    PropertyGroup * m_root;

};

} // namespace
