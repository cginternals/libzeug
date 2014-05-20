
#pragma once

#include <QList>

#include <signalzeug/ScopedConnection.h>


namespace reflectionzeug
{
    class AbstractProperty;
    class AbstractValueProperty;
    class PropertyGroup;
}

namespace propertyguizeug
{
    
class PropertyModel;

class PropertyItem
{
public:
    PropertyItem(reflectionzeug::AbstractProperty * collection,
                 PropertyModel * model);

    ~PropertyItem();

    reflectionzeug::AbstractProperty * property() const;

    int index() const;
    bool isEnabled() const;

    PropertyItem * parent() const;
    void setParent(PropertyItem * parent);
    bool hasParent() const;

    bool hasChildren() const;
    size_t childCount() const;

    PropertyItem * at(size_t i) const;

    int indexOf(const PropertyItem * item) const;

    void insertChild(size_t i, PropertyItem * item);
    bool removeChild(size_t i);

    void appendChild(PropertyItem * item);

private:
    reflectionzeug::AbstractProperty * m_property;

    PropertyItem * m_parent;
    QList<PropertyItem *> m_children;

    QList<signalzeug::ScopedConnection> m_connections;
};

} // namespace propertyguizeug
