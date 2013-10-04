
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <QSpinBox>

namespace zeug {

template <typename Type>
class Property;

class PROPERTYGUIZEUG_API IntegerEditor : public QSpinBox
{
public:
    IntegerEditor(Property<int> * property, QWidget * parent = nullptr);
    virtual ~IntegerEditor();

protected:
    Property<int> * m_property;
};

} // namespace
