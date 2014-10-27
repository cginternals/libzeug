
#pragma once

#include <propertyguizeug/PropertyEditor.h>

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
    using PropertyType = reflectionzeug::AbstractValueProperty;
    
public:
    ValueEditor(reflectionzeug::AbstractValueProperty * property, QWidget * parent = nullptr);
    virtual ~ValueEditor();
    
    void editingFinished();

protected:
    QLineEdit * m_lineEdit;
    
    reflectionzeug::AbstractValueProperty * m_property;
};

} // namespace propertyguizeug
