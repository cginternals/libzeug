
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include "PropertyEditor.h"

class QLineEdit;
class QFileDialog;
class QHBoxLayout;

namespace reflectionzeug {
    template <typename Type>
    class Property;
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
