
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include "PropertyEditor.h"

namespace zeug {

template <typename Type>
class Property;

class PROPERTYGUIZEUG_API ChoiceEditor : public PropertyEditor
{
public:
    ChoiceEditor(Property<std::string> * property, QWidget * parent = nullptr);
    virtual ~ChoiceEditor();
    
    void setString(const QString & text);

protected:
    Property<std::string> * m_property;
};

} // namespace
