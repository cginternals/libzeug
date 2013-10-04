
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <QWidget>

class QLineEdit;
class ColorButton;

namespace zeug {

template <typename Type>
class Property;
class Color;

class PROPERTYGUIZEUG_API ColorEditor : public QWidget
{
public:
    ColorEditor(Property<Color> * property, QWidget * parent = nullptr);
    virtual ~ColorEditor();
    
    void openColorPicker();

protected:
    QColor qcolor() const;
    void setQColor(const QColor & qcolor);
    
    ColorButton * m_button;
    QLineEdit * m_lineEdit;
    
    Property<Color> * m_property;    
};

} // namespace
