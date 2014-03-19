
#pragma once

#include <propertyguizeug/PropertyEditor.h>

class QLineEdit;

namespace reflectionzeug 
{
    template <typename Type>
    class Property;
    class Color;
}

namespace propertyguizeug
{

class ColorButton;

class PROPERTYGUIZEUG_API ColorEditor : public PropertyEditor
{
public:
    ColorEditor(reflectionzeug::Property<reflectionzeug::Color> * property, QWidget * parent = nullptr);
    virtual ~ColorEditor();
    
    void openColorPicker();
    void parseColor();

protected:
    QColor qcolor() const;
    void setQColor(const QColor & qcolor);
    void setColor(const reflectionzeug::Color & color);
    
protected:
    ColorButton * m_button;
    QLineEdit * m_lineEdit;
    
    reflectionzeug::Property<reflectionzeug::Color> * m_property;    
};

} // namespace propertyguizeug
