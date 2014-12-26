#include <widgetzeug/ColorGradientWidget.h>

#include <QLabel>
#include <QResizeEvent>
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
    auto layout = new QVBoxLayout{this};
    layout->setSpacing(1);

    layout->addWidget(m_label);
    layout->addWidget(m_bar);
}

ColorGradientWidget::~ColorGradientWidget() = default;

ColorGradient ColorGradientWidget::gradient() const
{
    return m_model->gradient();
}
    
void ColorGradientWidget::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);
}



} // namespace widgetzeug