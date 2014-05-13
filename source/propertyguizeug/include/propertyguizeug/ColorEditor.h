
#pragma once

#include <reflectionzeug/property_declaration.h>

#include <propertyguizeug/PropertyEditor.h>


class QLineEdit;

namespace reflectionzeug 
{
    class ColorPropertyInterface;
}

namespace propertyguizeug
{

class ColorButton;

class PROPERTYGUIZEUG_API ColorEditor : public PropertyEditor
{
public:
    ColorEditor(reflectionzeug::ColorPropertyInterface * property, QWidget * parent = nullptr);
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
    
    reflectionzeug::ColorPropertyInterface * m_property;    
};

} // namespace propertyguizeug
