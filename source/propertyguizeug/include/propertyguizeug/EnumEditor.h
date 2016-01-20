#pragma once

#include <signalzeug/ScopedConnection.h>

#include <propertyguizeug/PropertyEditor.h>
#include <propertyguizeug/ChoicesModel.h>

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
    ChoicesModel * m_model;
    signalzeug::ScopedConnection m_propertyChangedConnection;
};

} // namespace propertyguizeug
