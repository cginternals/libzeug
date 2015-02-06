#include <widgetzeug/ColorGradientWidget.h>

#include <type_traits>

#include <QComboBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeyEvent>
#include <QSpinBox>
#include <QVariant>

#include "ColorGradientLabel.h"
#include "ColorGradientMidpointBar.h"
#include "ColorGradientModel.h"
#include "ColorGradientStopBar.h"
#include "util.hpp"

#include "ui_ColorGradientWidget.h"

namespace
{
    using Gradient_underlying_type = std::underlying_type<widgetzeug::ColorGradientType>::type;
}

namespace widgetzeug
{

ColorGradientWidget::ColorGradientWidget(
    const ColorGradient & gradient,
    QWidget * parent)
:   QDialog{parent}
,   m_ui(new Ui_ColorGradientWidget())
{
    m_ui->setupUi(this);

    for (auto type : ColorGradient::types())
        m_ui->typeComboBox->addItem(ColorGradient::typeString(type), static_cast<Gradient_underlying_type>(type));

    setModel(make_unique<ColorGradientModel>(gradient));

    connect(m_ui->dataLinkWidget, &DataLinkWidget::fileChanged,
        this, &ColorGradientWidget::loadFromJson);

    connect(m_ui->dataLinkWidget, &DataLinkWidget::exportPressed,
        this, &ColorGradientWidget::saveToJson);
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

void ColorGradientWidget::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        return;

    QDialog::keyPressEvent(event);
}

void ColorGradientWidget::loadFromJson(const QString & fileName)
{
    QFile jsonFile{fileName};

    if (!jsonFile.open(QFile::ReadOnly))
        return;

    const auto jsonDocument = QJsonDocument::fromJson(jsonFile.readAll());

    if (jsonDocument.isNull() || jsonDocument.isEmpty() || !jsonDocument.isObject())
        return;

    const auto gradient = ColorGradient::fromJson(jsonDocument.object());
    setModel(make_unique<ColorGradientModel>(gradient));
}

void ColorGradientWidget::saveToJson(const QString & fileName)
{
    if (fileName.isNull())
        return;

    QFile jsonFile{fileName};

    if (!jsonFile.open(QFile::WriteOnly))
        return;

    const auto jsonDocument = QJsonDocument{gradient().toJson()};
    jsonFile.write(jsonDocument.toJson());
}

void ColorGradientWidget::updateStepsState()
{
    const bool enableSteps = static_cast<ColorGradientType>(m_model->type()) != ColorGradientType::Linear;

    m_ui->stepsLabel->setEnabled(enableSteps);
    m_ui->stepsSpinBox->setEnabled(enableSteps);
}

void ColorGradientWidget::setModel(std::unique_ptr<ColorGradientModel> && model)
{
    std::swap(m_model, model);

    m_ui->midpointBar->setModel(m_model.get());
    m_ui->label->setModel(m_model.get());
    m_ui->stopBar->setModel(m_model.get());

    const auto index = m_ui->typeComboBox->findData(static_cast<Gradient_underlying_type>(m_model->type()));
    m_ui->typeComboBox->setCurrentIndex(index);

    m_ui->stepsSpinBox->setValue(m_model->steps());

    updateStepsState();
}

void ColorGradientWidget::on_typeComboBox_currentIndexChanged(const int index)
{    
    if (!m_model)
        return;

    m_model->setType(m_ui->typeComboBox->itemData(index));
    updateStepsState();
};

void ColorGradientWidget::on_stepsSpinBox_valueChanged(const int value)
{
    if (!m_model)
        return;

    m_model->setSteps(value);
};


} // namespace widgetzeug
