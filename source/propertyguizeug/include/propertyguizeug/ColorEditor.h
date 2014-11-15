#pragma once

#include <reflectionzeug/property_declaration.h>

#include <propertyguizeug/PropertyEditor.h>

class QColor;
class QLineEdit;
class QPainter;
class QStyleOptionViewItem;

namespace reflectionzeug 
{
    class Color;
    class ColorPropertyInterface;
}

namespace propertyguizeug
{

class ColorButton;

class PROPERTYGUIZEUG_API ColorEditor : public PropertyEditor
{
public:
    static void paint(QPainter * painter, 
                      const QStyleOptionViewItem & option, 
                      reflectionzeug::ColorPropertyInterface & property);

public:
    ColorEditor(reflectionzeug::ColorPropertyInterface * property, 
                QWidget * parent = nullptr);
    
    void openColorPicker();
    void parseColor();

private:
    QColor qColor() const;
    void setQColor(const QColor & qcolor);
    void setColor(const reflectionzeug::Color & color);
    
private:  
    ColorButton * m_button;
    QLineEdit * m_lineEdit;
    
    reflectionzeug::ColorPropertyInterface * m_property;    
};

} // namespace propertyguizeug
