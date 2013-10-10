
#pragma once

#include <QWidget>

class QLineEdit;

namespace zeug {

class ColorButton;

template <typename Type>
class Property;

class Color;


class ColorEditor : public QWidget
{
public:
    ColorEditor(Property<Color> * property, QWidget * parent = nullptr);
    virtual ~ColorEditor();
    
    void openColorPicker();
    void parseColor();

protected:
    QColor qcolor() const;
    void setQColor(const QColor & qcolor);
    void setColor(const Color & color);
    
    ColorButton * m_button;
    QLineEdit * m_lineEdit;
    
    Property<Color> * m_property;    
};

} // namespace
