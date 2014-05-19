#pragma once

#include <QHash>
#include <QList>
#include <QAbstractItemModel>

#include <propertyguizeug/propertyguizeug_api.h>


namespace reflectionzeug 
{
    class AbstractProperty;
    class PropertyGroup;
}


namespace propertyguizeug
{

class PropertyItem;  

class PROPERTYGUIZEUG_API PropertyModel : public QAbstractItemModel
{
public:
    PropertyModel(reflectionzeug::PropertyGroup * group, QObject * parent = nullptr);
    virtual ~PropertyModel();
    
    virtual QModelIndex index(int row, int column,
                              const QModelIndex & parentIndex = QModelIndex()) const;
    
    virtual QModelIndex parent(const QModelIndex & index) const;
    
    virtual int rowCount(const QModelIndex & parentIndex = QModelIndex()) const;
    
    virtual int columnCount(const QModelIndex & parentIndex = QModelIndex()) const;
    
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;

    void onValueChanged(PropertyItem * item);

    void onBeforeAdd(PropertyItem * item, size_t position, AbstractProperty * property);
    void onAfterAdd();

    void onBeforeRemove(PropertyItem * item, size_t position);
    void onAfterRemove();

private:
    static void addChildren(PropertyItem * item, PropertyGroup * group);
    static void addChild(PropertyItem * item, AbstractProperty * property);

    QModelIndex createIndex(PropertyItem * item, int column = 0);
    
private:
    PropertyItem * m_root;
};

} // namespace propertyguizeug
