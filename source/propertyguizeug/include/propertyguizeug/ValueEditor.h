#pragma once

#include <propertyguizeug/PropertyEditor.h>

#include <signalzeug/ScopedConnection.h>

class QLineEdit;

namespace reflectionzeug 
{
    class AbstractProperty;
}

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API ValueEditor : public PropertyEditor
{
public:
    ValueEditor(reflectionzeug::AbstractProperty * property, 
                QWidget * parent = nullptr);
    virtual ~ValueEditor();
    
    void editingFinished();

private:
    QLineEdit * m_lineEdit;
    
    reflectionzeug::AbstractProperty * m_property;
    signalzeug::ScopedConnection m_propertyChangedConnection;
};

} // namespace propertyguizeug
