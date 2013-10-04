
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <QWidget>

class QSpinBox;

namespace zeug {

template <typename Type>
class Property;

class PROPERTYGUIZEUG_API IntegerEditor : public QWidget
{
public:
    IntegerEditor(Property<int> * property, QWidget * parent = nullptr);
    virtual ~IntegerEditor();

protected:
    QSpinBox * m_spinBox;
    
    Property<int> * m_property;
};

} // namespace
