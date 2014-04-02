
#pragma once

#include <reflectionzeug/property_declaration.h>

#include <propertyguizeug/PropertyEditor.h>

class QLineEdit;
class QFileDialog;
class QHBoxLayout;

namespace reflectionzeug 
{
    class FilePath;
}

namespace propertyguizeug
{
    
class PROPERTYGUIZEUG_API FilePathEditor : public PropertyEditor
{
public:
    FilePathEditor(reflectionzeug::Property<reflectionzeug::FilePath> * property, QWidget * parent = nullptr);
    virtual ~FilePathEditor();
    
    void setFilePath();
    void handleItemActivated(const QString & text);
    
    QStringList recentlyUsedFilePaths();
    void pushRecentlyUsedFilePath(const QString & filePath);
    
    void openFileDialog();

private:
    static const QString s_openFileDialog;

protected:
    
    QLineEdit * m_lineEdit;
    bool m_dialogOpened;

    QString m_filePathFromDialog;
    
    reflectionzeug::Property<reflectionzeug::FilePath> * m_property;
};

} // namespace propertyguizeug
