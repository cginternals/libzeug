#pragma once

#include <propertyguizeug/PropertyEditor.h>
#include <signalzeug/Connection.h>

class QLineEdit;

namespace reflectionzeug 
{
    class AbstractValueProperty;
}

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API ValueEditor : public PropertyEditor
{
public:
    ValueEditor(reflectionzeug::AbstractValueProperty * property, 
                QWidget * parent = nullptr);
    virtual ~ValueEditor();
    
    void editingFinished();

private:
    QLineEdit * m_lineEdit;
    
    reflectionzeug::AbstractValueProperty * m_property;
    signalzeug::Connection m_propertyChangedConnection;
};

} // namespace propertyguizeug
