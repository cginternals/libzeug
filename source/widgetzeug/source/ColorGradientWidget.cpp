#include <widgetzeug/ColorGradientWidget.h>

#include <QLabel>
#include <QResizeEvent>
#include <QVBoxLayout>

#include <widgetzeug/ColorGradient.h>

#include "ColorGradientStopBar.h"

namespace widgetzeug
{

ColorGradientWidget::ColorGradientWidget(
    const ColorGradient & gradient,
    QWidget * parent)
:   QWidget{parent}
{
    auto layout = new QVBoxLayout{this};
    layout->setSpacing(1);
    m_bar = new ColorGradientStopBar{gradient.stops(), this};
    m_gradientLabel = new QLabel{this};
    layout->addWidget(m_gradientLabel);
    layout->addWidget(m_bar);
    
    auto image = gradient.image(1000, 15);
    m_gradientLabel->setPixmap(QPixmap::fromImage(image));
    m_gradientLabel->setScaledContents(true);
    m_gradientLabel->setContentsMargins(6, 0, 6, 0);
    
    connect(m_bar, &ColorGradientStopBar::onStopsChanged,
            this, &ColorGradientWidget::stopsChanged);
}

void ColorGradientWidget::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);
}

void ColorGradientWidget::stopsChanged()
{
    QList<ColorGradientStop> stops = m_bar->stops();
    
    auto gradient = ColorGradient{stops, ColorGradientType::Discrete};
    auto image = gradient.image(1000, 15);
    m_gradientLabel->setPixmap(QPixmap::fromImage(image));
}

} // namespace widgetzeug