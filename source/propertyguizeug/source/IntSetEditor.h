
#pragma once

#include "SetEditor.h"

namespace reflectionzeug {
    template <typename Type>
    class Property;
}

namespace propertyguizeug
{
    
class PROPERTYGUIZEUG_API IntSetEditor : public SetEditor
{
public:
    IntSetEditor(reflectionzeug::Property<std::set<int>> * property, QWidget * parent = nullptr);
    virtual ~IntSetEditor();
    
    virtual void setSet();

protected:
    reflectionzeug::Property<std::set<int>> * m_property;
    
};

} // namespace propertyguizeug
