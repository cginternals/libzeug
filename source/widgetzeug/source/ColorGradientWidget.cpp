#include <widgetzeug/ColorGradientWidget.h>

#include <QComboBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QVBoxLayout>

#include <widgetzeug/ColorGradient.h>

#include "ColorGradientLabel.h"
#include "ColorGradientModel.h"
#include "ColorGradientStopBar.h"
#include "util.hpp"

namespace widgetzeug
{

ColorGradientWidget::ColorGradientWidget(
    const ColorGradient & gradient,
    QWidget * parent)
:   QWidget{parent}
,   m_model{make_unique<ColorGradientModel>(gradient)}
,   m_label{new ColorGradientLabel{m_model.get(), this}}
,   m_bar{new ColorGradientStopBar{m_model.get(), this}}
{
    auto labelLayout = new QVBoxLayout{};
    labelLayout->setContentsMargins(6, 0, 6, 0);
    labelLayout->addWidget(m_label);

    auto gradientLayoutWidget = new QWidget{};
    auto gradientLayout = new QVBoxLayout{gradientLayoutWidget};
    gradientLayout->setSpacing(1);
    gradientLayout->addLayout(labelLayout);
    gradientLayout->addWidget(m_bar);
    gradientLayoutWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    
    auto comboBox = new QComboBox{};
    comboBox->addItems({"Linear", "Discrete", "Matze"});
    comboBox->setCurrentIndex(static_cast<int>(m_model->type()));
    
    auto spinBox = new QSpinBox{};
    spinBox->setValue(m_model->steps());
    spinBox->setMinimum(3);
    spinBox->setMaximum(256);
    
    auto formLayoutWidget = new QWidget{};
    formLayoutWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    
    auto formLayout = new QFormLayout{formLayoutWidget};
    formLayout->addRow("Type", comboBox);
    formLayout->addRow("Steps", spinBox);
    
    auto mainLayout = new QVBoxLayout{this};
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(gradientLayoutWidget);
    mainLayout->addWidget(formLayoutWidget);
    
    
    connect(comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        [this] (int index)
        {
            m_model->setType(static_cast<ColorGradientType>(index));
        });
    
    connect(spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
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

} // namespace widgetzeug