
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <QWidget>

namespace zeug {

template <typename Type>
class Property;

class PROPERTYGUIZEUG_API ChoiceEditor : public QWidget
{
public:
    ChoiceEditor(Property<std::string> * property, QWidget * parent = nullptr);
    virtual ~ChoiceEditor();
    
    void setString(const QString & text);

protected:
    Property<std::string> * m_property;
};

} // namespace
