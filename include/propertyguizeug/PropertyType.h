
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
    PropertyType() {};
    PropertyType(const PropertyType & type) {};
    PropertyType(AbstractProperty * property) {};
    ~PropertyType() {};
};

} // namespace

Q_DECLARE_METATYPE(propertyguizeug::PropertyType)
