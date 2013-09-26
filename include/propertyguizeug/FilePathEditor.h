
#pragma once

#include <QLineEdit>
#include <propertyzeug/Property.h>
#include "propertyguizeug.h"

class QFileDialog;
class QHBoxLayout;

namespace propertyguizeug {

using propertyzeug::Property;
using propertyzeug::FilePath;
    
class PROPERTYGUIZEUG_API FilePathEditor : public QLineEdit
{
public:
    FilePathEditor(Property<FilePath> * property, QWidget * parent = nullptr);
    virtual ~FilePathEditor();
    
    void setFilePath();
    void handleItemActivated(const QString & text);
    
    void openFileDialog();

protected:
    static const QString s_openFileDialog;
    
    Property<FilePath> * m_property;
    bool m_dialogOpened;
    QString m_filePathFromDialog;
    
};

} // namespace
