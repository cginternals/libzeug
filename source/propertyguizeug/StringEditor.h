
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <QLineEdit>

namespace zeug {

template <typename Type>
class Property;

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
