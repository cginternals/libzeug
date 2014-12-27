#include "ColorGradientStopModel.h"

namespace widgetzeug
{

ColorGradientStopModel::ColorGradientStopModel(
    const ColorGradientStop & stop,
    QObject * parent)
:   QObject{parent}
,   m_stop{stop}
,   m_canRemove{false}
{
}

bool ColorGradientStopModel::canRemove() const
{
    return m_canRemove;
}

void ColorGradientStopModel::setCanRemove(bool canRemove)
{
    m_canRemove = canRemove;
}

qreal ColorGradientStopModel::position() const
{
    return m_stop.position();
}

void ColorGradientStopModel::setPosition(qreal position)
{
    m_stop.setPosition(position);
    
    emit positionChanged();
    emit changed();
}

qreal ColorGradientStopModel::midpoint() const
{
    return m_stop.midpoint();
}

void ColorGradientStopModel::setMidpoint(qreal midpoint)
{
    m_stop.setMidpoint(midpoint);
    emit changed();
}

const QColor & ColorGradientStopModel::color() const
{
    return m_stop.color();
}

void ColorGradientStopModel::setColor(const QColor & color)
{
    m_stop.setColor(color);
    emit changed();
}

const ColorGradientStop & ColorGradientStopModel::stop() const
{
    return m_stop;
}

} // namespace widgetzeug