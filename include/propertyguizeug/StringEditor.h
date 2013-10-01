
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <QLineEdit>

namespace propertyzeug {
    template <typename Type>
    class Property;
}

namespace propertyguizeug {

using namespace propertyzeug;

class PROPERTYGUIZEUG_API StringEditor : public QLineEdit
{
public:
    StringEditor(Property<std::string> * property, QWidget * parent = nullptr);
    virtual ~StringEditor();
    
    void setString();

protected:
    Property<std::string> * m_property;
};

} // namespace
