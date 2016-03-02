#include <widgetzeug/DataLinkWidget.h>

#include <QDebug>

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QDirIterator>
#include <QCompleter>
#include <QStringListModel>

#include <widgetzeug/make_unique.hpp>

#include "ui_DataLinkWidget.h"


namespace widgetzeug
{

class FileExistsValidator : public QValidator
{
public:
    FileExistsValidator(QObject * parent) : QValidator{parent}
    {
    }

    State validate(QString & input, int & /*pos*/) const override
    {
        const auto fileInfo = QFileInfo{input};

        if (fileInfo.exists() && fileInfo.isFile())
            return Acceptable;

        return Intermediate;
    }
};


DataLinkWidget::DataLinkWidget(QWidget * /*parent*/)
:   m_watcher{new QFileSystemWatcher{this}}
,   m_watchFile{false}
,   m_ui{make_unique<Ui_DataLinkWidget>()}
{
    m_ui->setupUi(this);
    
    auto warningLabel = m_ui->fileNameWarningLabel;
    const auto icon = style()->standardIcon(QStyle::SP_MessageBoxWarning);
    const auto iconExtent = static_cast<int>(warningLabel->height() * 0.5f);
    warningLabel->setPixmap(icon.pixmap(iconExtent));
    
    m_ui->linkCheckBox->setChecked(m_watchFile);

    m_ui->fileNameComboBox->setValidator(new FileExistsValidator{m_ui->fileNameComboBox});

    connect(m_watcher, &QFileSystemWatcher::fileChanged, this, &DataLinkWidget::fileChanged);

    // register every file change to prevent unnecassary fileChanged emits
    connect(this, &DataLinkWidget::fileChanged, [this] (const QString & fileName) 
        {
            m_lastEmitedFileName = fileName;
        });
}

DataLinkWidget::~DataLinkWidget() = default;

void DataLinkWidget::addFileName(const QString & fileName_, const bool active)
{
    if (!isRecent(fileName_))
        m_ui->fileNameComboBox->addItem(fileName_);

    if (!active)
        return;

    const auto index = m_ui->fileNameComboBox->findText(fileName_);
    m_ui->fileNameComboBox->setCurrentIndex(index); // triggers not if current index is index
}

void DataLinkWidget::setFileName(const QString & fileName)
{
    addFileName(fileName, true);
}
QString DataLinkWidget::fileName() const
{
    return m_ui->fileNameComboBox->currentText();
}

QStringList DataLinkWidget::fileNames() const
{
    QStringList names;

    for (auto i = 0; i < m_ui->fileNameComboBox->count(); ++i)
        names << m_ui->fileNameComboBox->itemText(i);

    return names;
}

void DataLinkWidget::setFileLinked(const bool linked)
{
    m_ui->linkCheckBox->setChecked(linked);
}
bool DataLinkWidget::fileLinked() const
{
    return m_ui->linkCheckBox->isChecked();
}

void DataLinkWidget::setFileIssue(const bool enable)
{
    m_ui->fileNameWarningLabel->setVisible(enable);
}

void DataLinkWidget::setFilter(const QString & filter)
{
    m_filter = filter;
}

void DataLinkWidget::setReadOnly(bool enabled)
{
    m_ui->savePushButton->setEnabled(!enabled);
}

bool DataLinkWidget::readOnly() const
{
    return !m_ui->savePushButton->isEnabled();
}

bool DataLinkWidget::isRecent(const QString & fileName) const
{
    // Note: file name and absolute file name might be intentionally used 
    // for referencing application relative and absolute files ... 

    return -1 != m_ui->fileNameComboBox->findText(fileName);
}

QCompleter * DataLinkWidget::completer()
{
    return m_ui->fileNameComboBox->completer();
}

void DataLinkWidget::updateWatcher()
{
    if (!m_watchFile)
    {
        if (!m_watcher->files().isEmpty())
            m_watcher->removePaths(m_watcher->files());
    }
    else
    {
        m_watcher->addPath(fileName());
    }
}

bool DataLinkWidget::browse()
{
    const auto fileName = QFileDialog::getOpenFileName(this, windowTitle(), QString{}, {});

    if (fileName.isEmpty())
        return false;
    
    setFileName(fileName);
    return true;
}

void DataLinkWidget::save()
{
    if (fileName().isEmpty())
        browse();

    emit save(fileName());
}

void DataLinkWidget::on_browsePushButton_clicked(bool)
{
    browse();
}

void DataLinkWidget::on_savePushButton_clicked(bool)
{
    save();
}

void DataLinkWidget::on_fileNameComboBox_currentIndexChanged(const QString & text)
{
    if (text.isEmpty() || !m_lastEmitedFileName.compare(text))
        return;

    updateWatcher();
    emit fileChanged(text);
}

void DataLinkWidget::on_fileNameComboBox_editTextChanged(const QString & text)
{
    const auto fi = QFileInfo{text};
    const auto path = fi.path().isEmpty() ? QDir::currentPath() : fi.path();

    if (path == m_path)
        return;

    // replace fileNameComboBox completer model

    // add all files in current path

    m_path = path;
    QDirIterator iterator{m_path};

    auto list = QStringList{};
    while (iterator.hasNext())
    {
        const auto next = iterator.next();

        if (next.endsWith(".") || next.endsWith(".."))
            continue;

        if (next.startsWith("./"))
            list << next.right(next.length() - 2);

        list << next;
    }

    // add recent items contained in fileNameComboBox
    for (auto i = 0; i < m_ui->fileNameComboBox->count(); ++i)
    {
        const auto item = m_ui->fileNameComboBox->itemText(i);
        if (!list.contains(item))
            list << item;
    }

    completer()->setModel(new QStringListModel{list});
}

void DataLinkWidget::on_linkCheckBox_stateChanged(const int state)
{
    auto checkState = static_cast<Qt::CheckState>(state);
    m_watchFile = checkState == Qt::Checked;

    if (m_watchFile)
        emit fileChanged(fileName());

    updateWatcher();
}

} // namespace widgetzeug
