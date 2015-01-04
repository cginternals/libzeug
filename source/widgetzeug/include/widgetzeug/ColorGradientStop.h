#pragma once

#include <QColor>

#include <widgetzeug/widgetzeug_api.h>

namespace widgetzeug
{

class WIDGETZEUG_API ColorGradientStop
{
public:
    static const qreal s_defaultMidpoint;

public:
    ColorGradientStop(qreal position,
                      qreal midpoint = s_defaultMidpoint);

    ColorGradientStop(const QColor & color, 
                      qreal position, 
                      qreal midpoint = s_defaultMidpoint);

    qreal position() const;
    void setPosition(qreal position);

    qreal midpoint() const;
    void setMidpoint(qreal midpoint);

    const QColor & color() const;
    void setColor(const QColor & color);
    
    bool operator<(const ColorGradientStop & otherStop) const;
    bool operator==(const ColorGradientStop & otherStop) const;
    bool operator!=(const ColorGradientStop & otherStop) const;

private:
    qreal m_position;
    qreal m_midpoint;
    QColor m_color;
};

} // namespace widgetzeug
