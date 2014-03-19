
#pragma once

#include <propertyguizeug/PropertyEditor.h>


namespace reflectionzeug
{
    class EnumPropertyInterface;
}

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API EnumEditor : public PropertyEditor
{
public:
    EnumEditor(reflectionzeug::EnumPropertyInterface * property, QWidget * parent = nullptr);
    virtual ~EnumEditor();
    
    void setString(const QString & text);

protected:
    reflectionzeug::EnumPropertyInterface * m_property;
};

} // namespace propertyguizeug
