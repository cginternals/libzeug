
#pragma once

#include "SetEditor.h"

namespace zeug {
    
template <typename Type>
class Property;

class PROPERTYGUIZEUG_API IntSetEditor : public SetEditor
{
public:
    IntSetEditor(Property<std::set<int>> * property, QWidget * parent = nullptr);
    virtual ~IntSetEditor();
    
    virtual void setSet();

protected:
    Property<std::set<int>> * m_property;
    
};

} // namespace
