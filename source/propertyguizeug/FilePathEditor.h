
#pragma once

#include <QLineEdit>

class QFileDialog;
class QHBoxLayout;

namespace zeug 
{

template <typename Type>
class Property;
class FilePath;
    
class FilePathEditor : public QLineEdit
{
public:
    FilePathEditor(Property<FilePath> * property, QWidget * parent = nullptr);
    virtual ~FilePathEditor();
    
    void setFilePath();
    void handleItemActivated(const QString & text);
    
    QStringList recentlyUsedFilePaths();
    void pushRecentlyUsedFilePath(const QString & filePath);
    
    void openFileDialog();

private:
    static const QString s_openFileDialog;

protected:

    Property<FilePath> * m_property;
    bool m_dialogOpened;

    QString m_filePathFromDialog;    
};

} // namespace
