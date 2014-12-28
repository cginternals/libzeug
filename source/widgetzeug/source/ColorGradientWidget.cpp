#include <widgetzeug/ColorGradientWidget.h>

#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QVBoxLayout>

#include <widgetzeug/ColorGradient.h>

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
,   m_model{make_unique<ColorGradientModel>(gradient)}
,   m_ui(new Ui_ColorGradientWidget{})
{
    m_ui->setupUi(this);
    
    m_ui->midpointBar->setModel(m_model.get());
    m_ui->label->setModel(m_model.get());
    m_ui->stopBar->setModel(m_model.get());
    
    m_ui->typeComboBox->setCurrentIndex(static_cast<int>(m_model->type()));
    m_ui->stepsSpinBox->setValue(m_model->steps());
    
    updateStepsState();

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
}

ColorGradientWidget::~ColorGradientWidget() = default;

ColorGradient ColorGradientWidget::gradient() const
{
    return m_model->gradient();
}

void ColorGradientWidget::updateStepsState()
{
    bool enableSteps = m_model->type() == ColorGradientType::Linear ? false : true;
    
    m_ui->stepsLabel->setEnabled(enableSteps);
    m_ui->stepsSpinBox->setEnabled(enableSteps);
}

} // namespace widgetzeug