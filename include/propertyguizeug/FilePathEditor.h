
#pragma once

#include <QWidget>
#include <propertyzeug/Property.h>
#include "propertyguizeug.h"

class QFileDialog;
class QHBoxLayout;

namespace propertyguizeug {

using propertyzeug::Property;
using propertyzeug::FilePath;
    
class PROPERTYGUIZEUG_API FilePathEditor : public QWidget
{
public:
    FilePathEditor(Property<FilePath> * property, QWidget * parent = nullptr);
    virtual ~FilePathEditor();

protected:
    QHBoxLayout * m_layout;
    Property<FilePath> * m_property;
    
};

} // namespace
