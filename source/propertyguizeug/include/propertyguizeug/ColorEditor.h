
#pragma once


#include <reflectionzeug/property/property_declaration.h>

#include <signalzeug/ScopedConnection.h>

#include <propertyguizeug/PropertyEditor.h>


class QColor;
class QLineEdit;
class QPainter;
class QStyleOptionViewItem;


namespace reflectionzeug 
{
    class AbstractColorInterface;
}


namespace propertyguizeug
{


class ColorButton;


/** \brief Editor for color classes
 *
 * Supported options:
 * - alpha (bool) = true: activates/disables the alpha channel
 */  
class PROPERTYGUIZEUG_API ColorEditor : public PropertyEditor
{
public:
    using Type = reflectionzeug::AbstractColorInterface;


public:
    static void paint(QPainter * painter, 
                      const QStyleOptionViewItem & option, 
                      reflectionzeug::AbstractColorInterface & property);


public:
    ColorEditor(reflectionzeug::AbstractColorInterface * property, 
                QWidget * parent = nullptr);
    virtual ~ColorEditor();
    
    void openColorPicker();
    void parseColor();


protected:
    void setQColor(const QColor & qcolor);

    
protected:  
    ColorButton * m_button;
    QLineEdit * m_lineEdit;
    bool m_includeAlpha;
    
    reflectionzeug::AbstractColorInterface * m_property;
    signalzeug::ScopedConnection m_propertyChangedConnection;
};


} // namespace propertyguizeug
