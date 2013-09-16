
#pragma once

#include <QWidget>
#include <propertyzeug/Property.h>
#include "propertyguizeug.h"

class QColorDialog;

namespace propertyguizeug {

using namespace propertyzeug;
    
class PROPERTYGUIZEUG_API ColorEditor : public QWidget
{
public:
    ColorEditor(Property<Color> * property, QWidget * parent = nullptr);
    virtual ~ColorEditor();
    
    void setColor(const QColor & color);

protected:
    QColorDialog * m_dialog;
    Property<Color> * m_property;
    
};

} // namespace
