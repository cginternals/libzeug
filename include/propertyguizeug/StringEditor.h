
#pragma once

#include <QLineEdit>
#include <propertyzeug/Property.h>
#include "propertyguizeug.h"

namespace propertyguizeug {

using namespace propertyzeug;

class PROPERTYGUIZEUG_API StringEditor : public QLineEdit
{
public:
    StringEditor(Property<std::string> * property, QWidget * parent = nullptr);
    virtual ~StringEditor();

protected:
    Property<std::string> * m_property;
};

} // namespace
