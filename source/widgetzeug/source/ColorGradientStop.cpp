#include <widgetzeug/ColorGradientStop.h>

#include "util.hpp"

namespace widgetzeug
{

const qreal ColorGradientStop::s_defaultMidpoint = 0.5;

ColorGradientStop::ColorGradientStop(
    qreal position,
    qreal midpoint)
:   ColorGradientStop{QColor{}, position, midpoint}
{
}

ColorGradientStop::ColorGradientStop(
    const QColor & color, 
    qreal position, 
    qreal midpoint)
:   m_position{clamp(position, 0.0, 1.0)}
,   m_midpoint{clamp(midpoint, 0.0, 1.0)}
,   m_color{color}
{
}

qreal ColorGradientStop::position() const
{
    return m_position;
}

void ColorGradientStop::setPosition(qreal position)
{
    m_position = clamp(position, 0.0, 1.0);
}

qreal ColorGradientStop::midpoint() const
{
    return m_midpoint;
}

void ColorGradientStop::setMidpoint(qreal midpoint)
{
    m_midpoint = clamp(midpoint, 0.0, 1.0);
}

const QColor & ColorGradientStop::color() const
{
    return m_color;
}

void ColorGradientStop::setColor(const QColor & color)
{
    m_color = color;
}

bool ColorGradientStop::operator<(const ColorGradientStop & rhs) const
{
    return m_position < rhs.m_position;
}

bool ColorGradientStop::operator==(const ColorGradientStop & rhs) const
{
    return (m_position == rhs.m_position) &&
           (m_midpoint == rhs.m_midpoint) &&
           (m_color == rhs.m_color);
}

bool ColorGradientStop::operator!=(const ColorGradientStop & rhs) const
{
    return !(*this == rhs);
}

} // namespace widgetzeug
