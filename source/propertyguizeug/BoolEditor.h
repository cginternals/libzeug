
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <QCheckBox>

namespace zeug {

template <typename Type>
class Property;
    
class PROPERTYGUIZEUG_API BoolEditor : public QCheckBox
{
public:
    BoolEditor(Property<bool> * property, QWidget * parent = nullptr);
    virtual ~BoolEditor();

protected:
    Property<bool> * m_property;
};

} // namespace
