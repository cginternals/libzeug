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
    ValueEditor(reflectionzeug::AbstractValueProperty * property, 
                QWidget * parent = nullptr);
    
    void editingFinished();

private:
    QLineEdit * m_lineEdit;
    
    reflectionzeug::AbstractValueProperty * m_property;
};

} // namespace propertyguizeug
