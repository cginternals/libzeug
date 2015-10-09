#pragma once

#include <propertyguizeug/PropertyEditor.h>

#include <signalzeug/ScopedConnection.h>

namespace reflectionzeug
{
    class AbstractEnumInterface;
}

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API EnumEditor : public PropertyEditor
{
public:
    using Type = reflectionzeug::AbstractEnumInterface;
    
public:
    EnumEditor(reflectionzeug::AbstractEnumInterface * property, 
               QWidget * parent = nullptr);
    virtual ~EnumEditor();
    
    void setString(const QString & text);

private:
    reflectionzeug::AbstractEnumInterface * m_property;
    signalzeug::ScopedConnection m_propertyChangedConnection;
};

} // namespace propertyguizeug
