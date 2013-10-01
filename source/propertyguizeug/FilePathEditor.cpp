
#include <propertyguizeug/FilePathEditor.h>

#include <QDebug>
#include <QSettings>
#include <QApplication>
#include <QFileDialog>
#include <QVariant>
#include <QCompleter>
#include <QLineEdit>

#include <propertyzeug/Property.h>

namespace propertyguizeug {
    
const QString FilePathEditor::s_openFileDialog = "Open File Dialog …";
    
FilePathEditor::FilePathEditor(Property<FilePath> * property, QWidget * parent)
:   QLineEdit(parent)
,   m_property(property)
,   m_dialogOpened(false)
,   m_filePathFromDialog("")
{
    this->setText(QString::fromStdString(m_property->value().string()));
    
    QCompleter * completer = new QCompleter(this->recentlyUsedFilePaths() << s_openFileDialog, this);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    this->setCompleter(completer);
    
    this->connect(this, &QLineEdit::editingFinished,
                  this, &FilePathEditor::setFilePath);
    
    this->connect(completer, static_cast<void (QCompleter::*)(const QString &)>(&QCompleter::activated),
                  this, &FilePathEditor::handleItemActivated);
    
    this->connect(this, &QLineEdit::selectionChanged, [this] () {
        this->completer()->complete();
    });
    
}

FilePathEditor::~FilePathEditor()
{
}
    
QStringList FilePathEditor::recentlyUsedFilePaths()
{
    QSettings settings(QSettings::NativeFormat,
                       QSettings::UserScope,
                       QApplication::organizationName());
    
    return settings.value(QString::fromStdString(m_property->path()),
                          QVariant(QStringList())).toStringList();
}

void FilePathEditor::pushRecentlyUsedFilePath(const QString & filePath)
{
    QStringList list = this->recentlyUsedFilePaths();
    
    while (list.size() > 5)
        list.pop_front();
    
    if (!list.contains(filePath))
        list.push_back(filePath);
    
    QSettings settings(QSettings::NativeFormat,
                       QSettings::UserScope,
                       QApplication::organizationName());
    
    settings.setValue(QString::fromStdString(m_property->path()),
                      QVariant(list));
}
    
void FilePathEditor::handleItemActivated(const QString & text)
{
    if (text == s_openFileDialog)
        this->openFileDialog();
}
    
void FilePathEditor::setFilePath()
{
    QString filePath = m_dialogOpened ? m_filePathFromDialog : this->text();

    if (filePath.isEmpty() || filePath == s_openFileDialog)
        return;
    
    this->pushRecentlyUsedFilePath(filePath);
    m_property->setValue(filePath.toStdString());
}
    
void FilePathEditor::openFileDialog()
{
    m_dialogOpened = true;
    this->clear();
    QFileDialog * fileDialog = new QFileDialog(this);
    
    if (m_property->isFile()) {
        fileDialog->setFileMode(m_property->shouldExist() ?
                                QFileDialog::ExistingFile : QFileDialog::AnyFile);
    } else {
        fileDialog->setFileMode(QFileDialog::Directory);
    }
    
    this->connect(fileDialog, &QFileDialog::fileSelected,
                  [this] (const QString & file) {
                      m_filePathFromDialog = file;
                      this->setText(file);
                  });
    
    fileDialog->show();
}
    
} // namespace
