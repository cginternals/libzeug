
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <QWidget>

class QDoubleSpinBox;

namespace zeug {

template <typename Type>
class Property;

class PROPERTYGUIZEUG_API DoubleEditor : public QWidget
{
public:
    DoubleEditor(Property<double> * property, QWidget * parent = nullptr);
    virtual ~DoubleEditor();

protected:
    QDoubleSpinBox * m_spinBox;
    
    Property<double> * m_property;
};

} // namespace
