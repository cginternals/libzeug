#include <widgetzeug/DataWidget.h>

#include <QDebug>

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFileSystemWatcher>

#include "ui_DataWidget.h"

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

DataWidget::DataWidget(QWidget * parent)
:   m_ui{new Ui_DataWidget()}
,   m_watcher{new QFileSystemWatcher{this}}
,   m_watchFile{true}
{
    m_ui->setupUi(this);

    connect(
        m_ui->dialogButton, &QPushButton::pressed,
        this, &DataWidget::onButtonPressed);

    connect(
        m_ui->comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        this, &DataWidget::onComboBoxCurrentIndexChanged);

    connect(
        m_watcher, &QFileSystemWatcher::fileChanged,
        this, &DataWidget::fileChanged);
    
    connect(
        m_ui->checkBox, &QCheckBox::stateChanged,
        this, &DataWidget::onCheckBoxChanged);
    
    connect(
        m_ui->exportButton, &QPushButton::pressed,
        [this] () { emit exportPressed(m_ui->comboBox->currentText()); });
    
    m_ui->comboBox->setValidator(new FileExistsValidator{m_ui->comboBox});
    m_ui->checkBox->setCheckState(m_watchFile ? Qt::Checked : Qt::Unchecked);
}

void DataWidget::onButtonPressed()
{
    const auto fileName = QFileDialog::getOpenFileName(this);

    if (fileName.isNull())
        return;
    
    const auto fileInfo = QFileInfo{fileName};
    
    if (!fileInfo.exists() || !fileInfo.isFile())
        return;
    
    auto comboBox = m_ui->comboBox;
    
    if (!fileNameExists(fileName))
        comboBox->addItem(fileName);
        
    comboBox->setCurrentIndex(comboBox->findText(fileName));
}

void DataWidget::onComboBoxCurrentIndexChanged(int index)
{
    updateWatcher();
    emit fileChanged(m_ui->comboBox->currentText());
}

void DataWidget::onCheckBoxChanged(int state)
{
    auto checkState = static_cast<Qt::CheckState>(state);
    m_watchFile = checkState == Qt::Checked;
    
    if (m_watchFile)
        emit fileChanged(m_ui->comboBox->currentText());
    
    updateWatcher();
}

bool DataWidget::fileNameExists(const QString & fileName)
{
    for (auto i = 0; i < m_ui->comboBox->count(); ++i)
        if (fileName == m_ui->comboBox->itemText(i))
            return true;
        
    return false;
}

void DataWidget::updateWatcher()
{
    if (!m_watchFile && !m_watcher->files().isEmpty())
        m_watcher->removePaths(m_watcher->files());
    else
        m_watcher->addPath(m_ui->comboBox->currentText());
}

} // namespace widgetzeug
