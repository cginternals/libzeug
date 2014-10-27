
#pragma once

#include <QString>

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

/** \brief Editor for FilePath class
 *
 * Supported options:
 * - uniqueidentifier (std::string): used to save recent files with QSettings
 *
 * Supported flags:
 * - shouldexist
 * - isfile
 */    
class PROPERTYGUIZEUG_API FilePathEditor : public PropertyEditor
{
public:
    using PropertyType = reflectionzeug::Property<reflectionzeug::FilePath>;

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
    QString m_uniqueIdentifier;

    QString m_filePathFromDialog;
    
    reflectionzeug::Property<reflectionzeug::FilePath> * m_property;
};

} // namespace propertyguizeug
