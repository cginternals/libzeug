
#pragma once

#include <QWidget>
#include <propertyzeug/Property.h>
#include "propertyguizeug.h"

namespace propertyguizeug {

using namespace propertyzeug;

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
