
#include "FilePathEditor.h"

#include <QHBoxLayout>
#include <QSettings>
#include <QApplication>
#include <QFileDialog>
#include <QVariant>
#include <QCompleter>
#include <QLineEdit>

#include <propertyzeug/Property.h>

namespace zeug 
{
    
const QString FilePathEditor::s_openFileDialog = "Open File Dialog …";
    
FilePathEditor::FilePathEditor(Property<FilePath> * property, QWidget * parent)
:   QWidget(parent)
,   m_lineEdit(new QLineEdit(this))
,   m_dialogOpened(false)
,   m_filePathFromDialog("")
,   m_property(property)
{
    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->setContentsMargins(3, 0, 3, 0);
    layout->setSpacing(3);
    layout->addWidget(m_lineEdit);
    
    this->setFocusProxy(m_lineEdit);
    
    QCompleter * completer = new QCompleter(this->recentlyUsedFilePaths() << s_openFileDialog, this);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    
    m_lineEdit->setCompleter(completer);
    m_lineEdit->setText(QString::fromStdString(m_property->value().string()));
    
    this->connect(m_lineEdit, &QLineEdit::editingFinished,
                  this, &FilePathEditor::setFilePath);
    
    this->connect(completer, static_cast<void (QCompleter::*)(const QString &)>(&QCompleter::activated),
                  this, &FilePathEditor::handleItemActivated);
    
    this->connect(m_lineEdit, &QLineEdit::selectionChanged, [this] () {
        m_lineEdit->completer()->complete();
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
                      m_lineEdit->setText(file);
                  });
    
    fileDialog->show();
}
    
} // namespace
