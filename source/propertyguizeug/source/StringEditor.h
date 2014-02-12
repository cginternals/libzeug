
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include "PropertyEditor.h"


class QLineEdit;

namespace zeug 
{

template <typename Type>
class Property;

class PROPERTYGUIZEUG_API StringEditor : public PropertyEditor
{
public:
    StringEditor(Property<std::string> * property, QWidget * parent = nullptr);
    virtual ~StringEditor();
    
    void editingFinished();

protected:
    QLineEdit * m_lineEdit;
    
    Property<std::string> * m_property;
};

} // namespace
