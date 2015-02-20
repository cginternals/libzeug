#include <widgetzeug/DataLinkWidget.h>

#include <QDebug>

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFileSystemWatcher>

#include "ui_DataLinkWidget.h"


namespace widgetzeug
{

class FileExistsValidator : public QValidator
{
public:
    FileExistsValidator(QObject * parent) : QValidator{parent}
    {
    }

    State validate(QString & input, int & pos) const override
    {
        const auto fileInfo = QFileInfo{input};

        if (fileInfo.exists() && fileInfo.isFile())
            return Acceptable;

        return Intermediate;
    }
};


DataLinkWidget::DataLinkWidget(QWidget * parent)
:   m_ui{new Ui_DataLinkWidget()}
,   m_watcher{new QFileSystemWatcher{this}}
,   m_watchFile{true}
{
    m_ui->setupUi(this);

    // ToDo: use settings to preserve list of recent files - therefor this needs an identifier...
    // ToDO: also redo selection of last file -> or allow to modify from outside..
    // ToDo: combo box should not be editable -> introduces further errors, minimize ways of usage

    connect(m_watcher, &QFileSystemWatcher::fileChanged,
        this, &DataLinkWidget::fileChanged);

    m_ui->dataComboBox->setValidator(new FileExistsValidator{m_ui->dataComboBox});
    m_ui->linkCheckBox->setCheckState(m_watchFile ? Qt::Checked : Qt::Unchecked);
}

QString DataLinkWidget::linkedFileName() const
{
    return m_ui->dataComboBox->currentText();
}

bool DataLinkWidget::linkedFileExists() const
{   
    return QFile::exists(linkedFileName());
}

bool DataLinkWidget::isRecent(const QString & fileName)
{
    for (auto i = 0; i < m_ui->dataComboBox->count(); ++i)
        if (fileName == m_ui->dataComboBox->itemText(i))
            return true;

    return false;
}

void DataLinkWidget::updateWatcher()
{
    // ToDo: work with Absolute File path! -> starting application from different locations...
    if (!m_watchFile && !m_watcher->files().isEmpty())
        m_watcher->removePaths(m_watcher->files());
    else
        m_watcher->addPath(m_ui->dataComboBox->currentText()); 
}

bool DataLinkWidget::browse()
{
    // ToDo: use Settings for last Data Folder - use application folder initially
    // ToDO: validate file existance... - 
    // ToDo: allow for passing filters and dialog title

    const auto fileName = QFileDialog::getOpenFileName(this);

    if (fileName.isEmpty())
        return false;

    const auto fi = QFileInfo { fileName };
    //if (!fi.exists() || !fi.isFile())
    //    return;

    auto comboBox = m_ui->dataComboBox;
    if (!isRecent(fileName))
        comboBox->addItem(fileName, fi.absoluteFilePath());

    comboBox->setCurrentIndex(comboBox->findText(fileName));

    return true;
}

void DataLinkWidget::export_()
{
    // ToDo: empty linked file name should open save dialog instead of open dialog. 
    
    if (linkedFileName().isEmpty())
        browse();

    emit exportPressed(m_ui->dataComboBox->currentText());
}

void DataLinkWidget::on_browsePushButton_clicked(bool)
{
    browse();
}

void DataLinkWidget::on_exportPushButton_clicked(bool)
{
    export_();
}

void DataLinkWidget::on_dataComboBox_currentIndexChanged(const int index)
{
    updateWatcher();
    emit fileChanged(m_ui->dataComboBox->currentText());
}

void DataLinkWidget::on_linkCheckBox_stateChanged(const int state)
{
    auto checkState = static_cast<Qt::CheckState>(state);
    m_watchFile = checkState == Qt::Checked;

    if (m_watchFile)
        emit fileChanged(m_ui->dataComboBox->currentText());

    updateWatcher();
}


} // namespace widgetzeug
