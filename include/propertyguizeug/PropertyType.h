
#pragma once

#include <QMetaType>
#include "propertyguizeug.h"

namespace propertyzeug {
    class AbstractProperty;
}

namespace propertyguizeug {
    
using namespace propertyzeug;

class PROPERTYGUIZEUG_API PropertyType
{
public:
    PropertyType() : m_property(nullptr) {};
    PropertyType(const PropertyType & type) : m_property(type.property()) {};
    PropertyType(AbstractProperty * property) {};
    ~PropertyType() {};
    
    AbstractProperty * property() const { return m_property; };
    void setProperty(AbstractProperty * property) { m_property = property; };

protected:
    AbstractProperty * m_property;
};

} // namespace

Q_DECLARE_METATYPE(propertyguizeug::PropertyType)
