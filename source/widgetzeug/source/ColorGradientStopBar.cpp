#include "ColorGradientStopBar.h"

#include <algorithm>

#include <QDebug>
#include <QMouseEvent>
#include <QResizeEvent>

#include <widgetzeug/ColorGradient.h>
#include <widgetzeug/ColorGradientStop.h>

#include "ColorGradientStopWidget.h"
#include "util.hpp"

namespace
{

bool lessThan(
    widgetzeug::ColorGradientStopWidget * stop1,
    widgetzeug::ColorGradientStopWidget * stop2)
{
    return stop1->position() < stop2->position();
}
    
} // namespace

namespace widgetzeug
{

ColorGradientStopBar::ColorGradientStopBar(
    const QList<ColorGradientStop> & stops,
    QWidget * parent)
:   QWidget(parent)
{
    setMinimumWidth(100);
    setFixedHeight(15);
    setCursor(Qt::PointingHandCursor);
    
    for (const auto & stop : stops)
        newStop(stop.color(), stop.position());
}

void ColorGradientStopBar::newStop(
    const QColor & color,
    qreal position)
{
    position = clamp(position, 0.0, 1.0);
    auto stop = new ColorGradientStopWidget{color, position, this};
    stop->show();
    
    connect(stop, &ColorGradientStopWidget::onPositionChanged,
            this, &ColorGradientStopBar::stopPositionChanged);
    
    connect(stop, &ColorGradientStopWidget::onColorChanged,
            this, &ColorGradientStopBar::stopColorChanged);
    
    addStop(stop);
}

QList<ColorGradientStop> ColorGradientStopBar::stops() const
{
    auto stops = QList<ColorGradientStop>{};
    
    for (const auto stopWidget : m_stops)
        stops.append({ stopWidget->color(), stopWidget->position() });
    
    return stops;
}

void ColorGradientStopBar::resizeEvent(QResizeEvent * event)
{
    emit onResized(event->size());
}

void ColorGradientStopBar::mouseReleaseEvent(QMouseEvent * event)
{
    auto position = static_cast<qreal>(event->pos().x() - 6.5) / (width() - 13);
    auto color = ColorGradient{stops()}.interpolateColor(position);
    newStop(color, position);
}

void ColorGradientStopBar::stopPositionChanged(
    ColorGradientStopWidget * stopWidget)
{
    emit onStopsChanged();

    if (std::is_sorted(m_stops.begin(), m_stops.end(), lessThan))
        return;
    
    auto stopIt = std::find(m_stops.begin(), m_stops.end(), stopWidget);
    m_stops.erase(stopIt);
    
    addStop(stopWidget);
}

void ColorGradientStopBar::stopColorChanged(ColorGradientStopWidget * stopWidget)
{
    emit onStopsChanged();
}

void ColorGradientStopBar::addStop(
    widgetzeug::ColorGradientStopWidget * stopWidget)
{
    auto lowerBoundIt = std::lower_bound(m_stops.begin(), m_stops.end(), stopWidget, lessThan);
    auto upperBoundIt = std::upper_bound(m_stops.begin(), m_stops.end(), stopWidget, lessThan);
    
    if (upperBoundIt == m_stops.end())
        stopWidget->raise();
    else
        stopWidget->stackUnder(*upperBoundIt);
    
    m_stops.insert(lowerBoundIt, stopWidget);
}

} // namespace widgetzeug