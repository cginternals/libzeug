#include <widgetzeug/DataWidget.h>

#include <QDebug>

#include <QFileDialog>
#include <QFileSystemWatcher>

#include "ui_DataWidget.h"

namespace widgetzeug
{

DataWidget::DataWidget(QWidget * parent)
:   m_ui{new Ui_DataWidget()}
,   m_watcher{new QFileSystemWatcher{this}}
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
        [] () { qDebug() << "something happened!"; });
}

void DataWidget::onButtonPressed()
{
    const auto fileName = QFileDialog::getOpenFileName(this);

    if (fileName.isNull())
        return;

    m_ui->comboBox->addItem(fileName);
    m_ui->comboBox->setCurrentText(fileName);
}

void DataWidget::onComboBoxCurrentIndexChanged(int index)
{
    if (!QFile::exists(m_ui->comboBox->currentText()))
    {
        m_ui->comboBox->removeItem(index);
        return;
    }

    if (m_watcher->addPath(m_ui->comboBox->currentText()))
        qDebug() << m_watcher->files();

    emit fileChanged(m_ui->comboBox->currentText());
}

} // namespace widgetzeug
