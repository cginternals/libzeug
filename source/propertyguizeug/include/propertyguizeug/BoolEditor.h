
#pragma once

#include <reflectionzeug/property_declaration.h>

#include <propertyguizeug/propertyguizeug_api.h>

#include <propertyguizeug/PropertyEditor.h>

namespace propertyguizeug
{
    
class PROPERTYGUIZEUG_API BoolEditor : public PropertyEditor
{
public:
    BoolEditor(reflectionzeug::Property<bool> * property, QWidget * parent = nullptr);
    virtual ~BoolEditor();

protected:
    reflectionzeug::Property<bool> * m_property;

};

} // namespace propertyguizeug
