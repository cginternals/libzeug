#pragma once

#include <QObject>

#include <widgetzeug/ColorGradientStop.h>

namespace widgetzeug
{

class ColorGradientStopModel : public QObject
{
    Q_OBJECT

public:
    ColorGradientStopModel(const ColorGradientStop & stop);

    qreal position() const;
    void setPosition(qreal position);

    qreal midpoint() const;
    void setMidpoint(qreal midpoint);

    const QColor & color() const;
    void setColor(const QColor & color);

    const ColorGradientStop & stop() const;

signals:
    void changed();

private:
    ColorGradientStop m_stop;
};

} // namespace widgetzeug