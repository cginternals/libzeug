
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include "PropertyEditor.h"


class QLineEdit;

namespace reflectionzeug 
{
    class ValuePropertyInterface;
}

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API ValueEditor : public PropertyEditor
{
public:
    ValueEditor(reflectionzeug::ValuePropertyInterface * property, QWidget * parent = nullptr);
    virtual ~ValueEditor();
    
    void editingFinished();

protected:
    QLineEdit * m_lineEdit;
    
    reflectionzeug::ValuePropertyInterface * m_property;
};

} // namespace propertyguizeug
