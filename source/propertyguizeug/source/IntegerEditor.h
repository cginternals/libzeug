
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include "PropertyEditor.h"


class QSpinBox;

namespace zeug 
{

template <typename Type>
class Property;

class PROPERTYGUIZEUG_API IntegerEditor : public PropertyEditor
{
public:
    IntegerEditor(Property<int> * property, QWidget * parent = nullptr);
    virtual ~IntegerEditor();

protected:
    QSpinBox * m_spinBox;
    
    Property<int> * m_property;
};

} // namespace
