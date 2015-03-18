#pragma once

#include <reflectionzeug/property_declaration.h>
#include <signalzeug/ScopedConnection.h>

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

/** \brief Editor for Color class
 *
 * Supported options:
 * - alpha (bool) = true: activates/disables the alpha channel
 */  
class PROPERTYGUIZEUG_API ColorEditor : public PropertyEditor
{
public:
    using Type = reflectionzeug::ColorPropertyInterface;

    static void paint(QPainter * painter, 
                      const QStyleOptionViewItem & option, 
                      reflectionzeug::ColorPropertyInterface & property);

public:
    ColorEditor(reflectionzeug::ColorPropertyInterface * property, 
                QWidget * parent = nullptr);
    virtual ~ColorEditor();
    
    void openColorPicker();
    void parseColor();

private:
    QColor qColor() const;
    void setQColor(const QColor & qcolor);
    void setColor(const reflectionzeug::Color & color);
    
private:  
    ColorButton * m_button;
    QLineEdit * m_lineEdit;
    bool m_alpha;
    
    reflectionzeug::ColorPropertyInterface * m_property;
    signalzeug::ScopedConnection m_propertyChangedConnection;
};

} // namespace propertyguizeug
