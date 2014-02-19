
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include "PropertyEditor.h"

namespace reflectionzeug {
    template <typename Type>
    class Property;
}

namespace propertyguizeug
{
    
class BoolEditor : public PropertyEditor
{
public:
    BoolEditor(reflectionzeug::Property<bool> * property, QWidget * parent = nullptr);
    virtual ~BoolEditor();

protected:
    reflectionzeug::Property<bool> * m_property;

};

} // namespace propertyguizeug
