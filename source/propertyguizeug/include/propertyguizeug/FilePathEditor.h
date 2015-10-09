#pragma once

#include <QString>

#include <reflectionzeug/property/property_declaration.h>

#include <signalzeug/ScopedConnection.h>

#include <propertyguizeug/PropertyEditor.h>

class QLineEdit;

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
 * - shouldexist (bool)
 * - isfile (bool)
 */    
class PROPERTYGUIZEUG_API FilePathEditor : public PropertyEditor
{
public:
    using Type = reflectionzeug::Property<reflectionzeug::FilePath>;
    
public:
    FilePathEditor(reflectionzeug::Property<reflectionzeug::FilePath> * property, 
                   QWidget * parent = nullptr);
    virtual ~FilePathEditor();
    
    void setFilePath();
    void handleItemActivated(const QString & text);
    
    QStringList recentlyUsedFilePaths();
    void pushRecentlyUsedFilePath(const QString & filePath);
    
    void openFileDialog();

private:
    static const QString s_openFileDialog;

private:
    QLineEdit * m_lineEdit;
    bool m_dialogOpened;
    QString m_uniqueIdentifier;
    QString m_filePathFromDialog;
    
    reflectionzeug::Property<reflectionzeug::FilePath> * m_property;
    signalzeug::ScopedConnection m_propertyChangedConnection;
};

} // namespace propertyguizeug
