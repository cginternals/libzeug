
#include <QFileDialog>
#include <QCompleter>
#include <QLineEdit>
#include <propertyguizeug/FilePathEditor.h>

namespace propertyguizeug {
    
const QString FilePathEditor::s_openFileDialog = "Open File Dialog …";
    
FilePathEditor::FilePathEditor(Property<FilePath> * property, QWidget * parent)
:   QLineEdit(parent)
,   m_property(property)
,   m_dialogOpened(false)
,   m_filePathFromDialog("")
{
    this->setText(QString::fromStdString(m_property->value().string()));
    QCompleter * completer = new QCompleter({"/User/max/doc.txt", "~/Downloads/text.txt", "~/Desktop/picture.png", s_openFileDialog}, this);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    this->setCompleter(completer);
    
    this->connect(this, &QLineEdit::editingFinished,
                  this, &FilePathEditor::setFilePath);
    
    this->connect(completer, static_cast<void (QCompleter::*)(const QString &)>(&QCompleter::activated),
                  this, &FilePathEditor::handleItemActivated);
    
}

FilePathEditor::~FilePathEditor()
{
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
                      this->clearFocus();
                  });
    
    fileDialog->show();
}
    
} // namespace
