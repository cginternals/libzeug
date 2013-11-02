
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include "PropertyEditor.h"

namespace zeug 
{

template <typename Type>
class Property;
    
class BoolEditor : public PropertyEditor
{
public:
    BoolEditor(Property<bool> * property, QWidget * parent = nullptr);
    virtual ~BoolEditor();

protected:
    Property<bool> * m_property;

};

} // namespace
