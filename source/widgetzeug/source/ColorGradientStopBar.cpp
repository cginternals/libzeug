#include "ColorGradientStopBar.h"

#include <algorithm>

#include <QMouseEvent>
#include <QResizeEvent>

#include <widgetzeug/ColorGradient.h>
#include <widgetzeug/ColorGradientStop.h>

#include "ColorGradientModel.h"
#include "ColorGradientStopModel.h"
#include "ColorGradientStopWidget.h"
#include "util.hpp"

namespace
{

bool lessThan(
    widgetzeug::ColorGradientStopWidget * widget1,
    widgetzeug::ColorGradientStopWidget * widget2)
{
    return widget1->model()->position() < widget2->model()->position();
}
    
} // namespace

namespace widgetzeug
{

ColorGradientStopBar::ColorGradientStopBar(
    ColorGradientModel * model,
    QWidget * parent)
:   QWidget{parent}
,   m_model{model}
{
    setMinimumWidth(100);
    setFixedHeight(16);
    setCursor(Qt::PointingHandCursor);
    
    for (auto stopModel : m_model->stopModels())
        newStop(stopModel);
}

void ColorGradientStopBar::resizeEvent(QResizeEvent * event)
{
    emit resized(event->size());
}

void ColorGradientStopBar::mouseReleaseEvent(QMouseEvent * event)
{
    auto position = static_cast<qreal>(event->pos().x() - 6.5) / (width() - 13);
    auto color = m_model->interpolateColor(position);
    
    auto stopModel = m_model->newStop({color, position});
    newStop(stopModel);
}

void ColorGradientStopBar::onStopPositionChanged(
    ColorGradientStopWidget * stopWidget)
{
    if (std::is_sorted(m_stopWidgets.begin(), m_stopWidgets.end(), lessThan))
        return;
    
    auto stopIt = std::find(m_stopWidgets.begin(), m_stopWidgets.end(), stopWidget);
    m_stopWidgets.erase(stopIt);
    
    addStop(stopWidget);
}

void ColorGradientStopBar::onStopRemove(ColorGradientStopWidget * stopWidget)
{
    auto stopModel = stopWidget->model();
    m_stopWidgets.removeOne(stopWidget);
    m_model->removeStop(stopModel);
    delete stopWidget;
}

void ColorGradientStopBar::newStop(ColorGradientStopModel * stopModel)
{
    auto stopWidget = new ColorGradientStopWidget{stopModel, this};
    stopWidget->show();
    
    connect(stopWidget, &ColorGradientStopWidget::positionChanged,
            this, &ColorGradientStopBar::onStopPositionChanged);
    
    connect(stopWidget, &ColorGradientStopWidget::remove,
            this, &ColorGradientStopBar::onStopRemove);
    
    connect(this, &ColorGradientStopBar::resized,
            stopWidget, &ColorGradientStopWidget::updatePosition);
    
    addStop(stopWidget);
}
    
void ColorGradientStopBar::addStop(
    widgetzeug::ColorGradientStopWidget * stopWidget)
{
    auto lowerBoundIt = std::lower_bound(m_stopWidgets.begin(), m_stopWidgets.end(), stopWidget, lessThan);
    auto upperBoundIt = std::upper_bound(m_stopWidgets.begin(), m_stopWidgets.end(), stopWidget, lessThan);
    
    if (upperBoundIt == m_stopWidgets.end())
        stopWidget->raise();
    else
        stopWidget->stackUnder(*upperBoundIt);
    
    m_stopWidgets.insert(lowerBoundIt, stopWidget);
}

} // namespace widgetzeug