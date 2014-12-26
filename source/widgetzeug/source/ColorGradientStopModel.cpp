#include "ColorGradientStopModel.h"

namespace widgetzeug
{

ColorGradientStopModel::ColorGradientStopModel(
    const ColorGradientStop & stop)
:   m_stop(stop)
{
}

qreal ColorGradientStopModel::position() const
{
    return m_stop.position();
}

void ColorGradientStopModel::setPosition(qreal position)
{
    m_stop.setPosition(position);
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