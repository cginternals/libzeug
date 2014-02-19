
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include "PropertyEditor.h"


class QSpinBox;
namespace reflectionzeug {
    template <typename Type>
    class Property;
}

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API IntegerEditor : public PropertyEditor
{
public:
    IntegerEditor(reflectionzeug::Property<int> * property, QWidget * parent = nullptr);
    virtual ~IntegerEditor();

protected:
    QSpinBox * m_spinBox;
    
    reflectionzeug::Property<int> * m_property;
};

} // namespace propertyguizeug
