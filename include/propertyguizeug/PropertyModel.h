
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <QList>
#include <QAbstractItemModel>

namespace zeug {
    
class ScopedConnection;
class PropertyGroup;

class PROPERTYGUIZEUG_API PropertyModel : public QAbstractItemModel
{
public:
    PropertyModel(PropertyGroup * root, QObject * parent = nullptr);
    virtual ~PropertyModel();
    
    void subscribeToValueChanges();
    
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
    QList<ScopedConnection> m_connectionList;

};

} // namespace zeug
