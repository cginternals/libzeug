#include <widgetzeug/ColorGradientWidget.h>

#include <QComboBox>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QSpinBox>

#include "ColorGradientLabel.h"
#include "ColorGradientMidpointBar.h"
#include "ColorGradientModel.h"
#include "ColorGradientStopBar.h"
#include "util.hpp"

#include "ui_ColorGradientWidget.h"

namespace widgetzeug
{

ColorGradientWidget::ColorGradientWidget(
    const ColorGradient & gradient,
    QWidget * parent)
:   QDialog{parent}
,   m_ui(new Ui_ColorGradientWidget())
{
    m_ui->setupUi(this);

    setModel(make_unique<ColorGradientModel>(gradient));

    m_ui->typeComboBox->addItems(ColorGradient::s_typeStringMap.values());

    connect(m_ui->typeComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        [this] (int index)
        {
            m_model->setType(static_cast<ColorGradientType>(index));
            updateStepsState();
        });

    connect(m_ui->stepsSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
        [this] (int value)
        {
            m_model->setSteps(value);
        });
    
    connect(
        m_ui->dataWidget, &DataWidget::fileChanged,
        this, &ColorGradientWidget::loadFromJson);
}

ColorGradientWidget::~ColorGradientWidget() = default;

ColorGradient ColorGradientWidget::gradient() const
{
    return m_model->gradient();
}

void ColorGradientWidget::setHistogram(const QList<uint> & histogram)
{
    m_ui->label->setHistogram(histogram);
}

void ColorGradientWidget::loadFromJson(const QString & fileName)
{
    QFile jsonFile{fileName};

    if (!jsonFile.open(QFile::ReadOnly))
    {
        QMessageBox::information(this, {}, "File could not be opened.");
        return;
    }

    const auto jsonDocument = QJsonDocument::fromJson(jsonFile.readAll());

    if (jsonDocument.isNull() || jsonDocument.isEmpty() || !jsonDocument.isObject())
    {
        QMessageBox::information(this, {}, "Json is ill-formed.");
        return;
    }

    const auto gradient = ColorGradient::fromJson(jsonDocument.object());
    setModel(make_unique<ColorGradientModel>(gradient));
}

void ColorGradientWidget::saveToJson()
{
    const auto fileName = QFileDialog::getSaveFileName(this);

    if (fileName.isNull())
        return;

    QFile jsonFile{fileName};

    if (!jsonFile.open(QFile::WriteOnly))
    {
        QMessageBox::information(this, {}, "Could not write to file.");
        return;
    }

    const auto jsonDocument = QJsonDocument{gradient().toJson()};
    jsonFile.write(jsonDocument.toJson());
}

void ColorGradientWidget::updateStepsState()
{
    bool enableSteps = m_model->type() == ColorGradientType::Linear ? false : true;

    m_ui->stepsLabel->setEnabled(enableSteps);
    m_ui->stepsSpinBox->setEnabled(enableSteps);
}

void ColorGradientWidget::setModel(std::unique_ptr<ColorGradientModel> && model)
{
    std::swap(m_model, model);

    m_ui->midpointBar->setModel(m_model.get());
    m_ui->label->setModel(m_model.get());
    m_ui->stopBar->setModel(m_model.get());

    m_ui->typeComboBox->setCurrentIndex(static_cast<int>(m_model->type()));
    m_ui->stepsSpinBox->setValue(m_model->steps());

    updateStepsState();
}

} // namespace widgetzeug
