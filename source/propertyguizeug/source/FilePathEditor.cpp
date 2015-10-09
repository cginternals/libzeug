#include <propertyguizeug/FilePathEditor.h>

#include <QCompleter>
#include <QFileDialog>
#include <QLineEdit>
#include <QSettings>
#include <QVariant>

#include <reflectionzeug/property/Property.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
const QString FilePathEditor::s_openFileDialog = "Open File Dialog …";
    
FilePathEditor::FilePathEditor(Property<FilePath> * property, QWidget * parent)
:   PropertyEditor{parent}
,   m_lineEdit{new QLineEdit{this}}
,   m_dialogOpened{false}
,   m_property{property}
{
    if (m_property->hasOption("uniqueidentifier"))
        m_uniqueIdentifier = QString::fromStdString(m_property->option("uniqueidentifier").value<std::string>());
    else
        m_uniqueIdentifier = QString::fromStdString(m_property->name());
        
    addWidget(m_lineEdit);
    setFocusProxy(m_lineEdit);
    
    auto completer = new QCompleter(this->recentlyUsedFilePaths() << s_openFileDialog, this);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    
    m_lineEdit->setCompleter(completer);
    m_lineEdit->setText(QString::fromStdString(m_property->value().string()));
    
    connect(m_lineEdit, &QLineEdit::editingFinished,
                  this, &FilePathEditor::setFilePath);
    
    using StringActivatedPtr = void (QCompleter::*)(const QString &);
    connect(completer, static_cast<StringActivatedPtr>(&QCompleter::activated),
            this, &FilePathEditor::handleItemActivated);
    
    connect(m_lineEdit, &QLineEdit::selectionChanged, 
        [this]()
        {
            m_lineEdit->completer()->complete();
        });

    m_propertyChangedConnection = m_property->valueChanged.connect(
        [this](const reflectionzeug::FilePath & newPath)
        {
            m_lineEdit->setText(QString::fromStdString(newPath.string()));
        });
}

FilePathEditor::~FilePathEditor()
{
}

QStringList FilePathEditor::recentlyUsedFilePaths()
{                       
    QSettings settings;
    return settings.value(m_uniqueIdentifier,
                          QVariant(QStringList())).toStringList();
}

void FilePathEditor::pushRecentlyUsedFilePath(const QString & filePath)
{
    auto filePaths = this->recentlyUsedFilePaths();
    
    while (filePaths.size() > 5)
        filePaths.pop_front();
    
    if (!filePaths.contains(filePath))
        filePaths.push_back(filePath);

    QSettings settings;    
    settings.setValue(m_uniqueIdentifier,
                      QVariant(filePaths));
}
    
void FilePathEditor::handleItemActivated(const QString & text)
{
    if (text == s_openFileDialog)
        this->openFileDialog();
}
    
void FilePathEditor::setFilePath()
{
    QString filePath = m_dialogOpened ? m_filePathFromDialog : m_lineEdit->text();

    if (filePath.isEmpty() || filePath == s_openFileDialog)
        return;
    
    this->pushRecentlyUsedFilePath(filePath);
    m_property->setValue(filePath.toStdString());
}
    
void FilePathEditor::openFileDialog()
{
    m_dialogOpened = true;
    m_lineEdit->clear();
    
    auto fileDialog = new QFileDialog{this};
    if (m_property->option("isfile").value<bool>(true))
    {
        fileDialog->setFileMode(m_property->option("shouldexist").value<bool>(true) ?
                                QFileDialog::ExistingFile : QFileDialog::AnyFile);
    } 
    else 
    {
        fileDialog->setFileMode(QFileDialog::Directory);
    }
    
    connect(fileDialog, &QFileDialog::fileSelected,
        [this] (const QString & file) 
        {
            m_filePathFromDialog = file;
            m_lineEdit->setText(file);
        });
    
    fileDialog->exec();
	
	m_dialogOpened = false;  
}
    
} // namespace propertyguizeug
