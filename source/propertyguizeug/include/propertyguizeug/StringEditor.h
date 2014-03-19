
#pragma once

#include <propertyguizeug/PropertyEditor.h>


class QLineEdit;
namespace reflectionzeug {
    template <typename Type>
    class Property;
}

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API StringEditor : public PropertyEditor
{
public:
    StringEditor(reflectionzeug::Property<std::string> * property, QWidget * parent = nullptr);
    virtual ~StringEditor();
    
    void editingFinished();

protected:
    QLineEdit * m_lineEdit;
    
    reflectionzeug::Property<std::string> * m_property;
};

} // namespace propertyguizeug
