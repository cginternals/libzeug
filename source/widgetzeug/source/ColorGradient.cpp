#include <widgetzeug/ColorGradient.h>

#include <algorithm>

#include <QDebug>
#include <QImage>
#include <QVector4D>

#include <widgetzeug/ColorScheme.h>

#include "util.hpp"

namespace 
{

QColor lerpColor(
    const widgetzeug::ColorGradientStop & stop1, 
    const widgetzeug::ColorGradientStop & stop2,
    qreal position)
{
    qreal pos = (position - stop1.position()) / (stop2.position() - stop1.position());
    qreal midpoint = stop1.midpoint();

    QColor color1 = stop1.color();
    QColor color2 = stop2.color();

    QVector4D vec1(color1.redF(), color1.greenF(), color1.blueF(), color1.alphaF());
    QVector4D vec2(color2.redF(), color2.greenF(), color2.blueF(), color2.alphaF());
    QVector4D avg((vec1 + vec2) / 2.0f);
    
    QVector4D result;
    if (pos > midpoint)
        result = widgetzeug::mix(avg, vec2, (pos - midpoint) / (1.0f - midpoint));
    else
        result = widgetzeug::mix(vec1, avg,  pos / midpoint);

    return QColor::fromRgbF(result.x(), result.y(), result.z(), result.w());
}

QColor makeLighter(const QColor & color, qreal factor)
{
    if (factor == 1.0)
        return color;
    
    auto hueF = 0.0, saturationF = 0.0, valueF = 0.0, alphaF = 0.0;
    color.getHsvF(&hueF, &saturationF, &valueF, &alphaF);
    valueF = widgetzeug::clamp(valueF * factor, 0.0, 1.0);
    return QColor::fromHsvF(hueF, saturationF, valueF, alphaF);
}

} // namespace

namespace widgetzeug
{

ColorGradient ColorGradient::fromScheme(
    ColorScheme * scheme, 
    int classes, 
    ColorGradientType type,
    uint steps)
{
    if (classes > scheme->maxClasses() || classes < scheme->minClasses())
        return ColorGradient();

    return fromList(scheme->colors(classes), type, steps);
}

ColorGradient ColorGradient::fromList(
    const QList<QColor> & colors,
    ColorGradientType type,
    uint steps)
{
    if (colors.count() < s_minNumStops)
        return ColorGradient();

    ColorGradient gradient(type, steps);

    const qreal dimension = 1.0 / (colors.count() - 1);

    for (int i = 0; i < colors.size(); ++i)
        gradient.addStop(ColorGradientStop(colors[i], dimension * i));

    return gradient;
}

QString ColorGradient::typeString(const ColorGradientType type)
{
    switch (type)
    {
        case ColorGradientType::Discrete:
            return "Discrete";
            
        case ColorGradientType::Linear:
            return "Linear";
            
        case ColorGradientType::Matze:
            return "Matze";
    };
    
    return "";
}

ColorGradient::ColorGradient(ColorGradientType type, uint steps)
:   ColorGradient(ColorGradientStops(), type, steps)
{
}

ColorGradient::ColorGradient(
    const ColorGradientStops & stops, 
    ColorGradientType type,
    uint steps)
:   m_type(type)
,   m_steps(steps)
{
    setStops(stops);
}

bool ColorGradient::isValid() const
{
    return m_stops.count() >= s_minNumStops;
}

void ColorGradient::addStop(const ColorGradientStop & stop)
{
    ColorGradientStops::iterator it = std::lower_bound(m_stops.begin(), m_stops.end(), stop);
    m_stops.insert(it, stop);
}

void ColorGradient::setStops(const ColorGradientStops & stops)
{
    m_stops = stops;
    std::stable_sort(m_stops.begin(), m_stops.end());
}

ColorGradientStops ColorGradient::stops() const
{
    return m_stops;
}

ColorGradientType ColorGradient::type() const
{
    return m_type;
}

void ColorGradient::setType(ColorGradientType type)
{
    m_type = type;
}

uint ColorGradient::steps() const
{
    return m_steps;
}

void ColorGradient::setSteps(uint steps)
{
    m_steps = std::max(steps, 2u);
}

QColor ColorGradient::interpolateColor(qreal position) const
{
    if (m_type == ColorGradientType::Linear)
        return linearInterpolateColor(position);
        
    if (!isValid())
        return QColor();
            
    qreal discretePosition = qFloor(position * m_steps) / (qreal)m_steps;
    discretePosition *= 1.0 + 1.0 / (m_steps - 1);
    
    if (m_type == ColorGradientType::Discrete)
        return linearInterpolateColor(discretePosition);
    
    const auto discreteColor = linearInterpolateColor(discretePosition);
    const auto valueF = discreteColor.valueF();
    
    // Because valueF can't be greater 1.0, the stretchingFactor ensures
    // that it still increases over the whole intervall.
    const auto stretchingFactor = 1.0 / 0.15 * (1.0 / valueF - 1.0);

    auto relativePosFactor = 0.0;
    if (stretchingFactor >= 1.0)
        relativePosFactor = fract(position * m_steps);
    else
        relativePosFactor = fract(position * m_steps) * stretchingFactor;
    
    const auto lighteningFactor = 1.0 + relativePosFactor * 0.15;
    
    return makeLighter(discreteColor, lighteningFactor);
}

QImage ColorGradient::image(uint width) const
{
    if (!isValid())
        return QImage();

    QImage image(width, 1, QImage::Format_ARGB32);

    for (uint i = 0; i < width; ++i)
    {
        qreal position = (qreal)i / width;
        image.setPixel(i, 0, interpolateColor(position).rgba());
    }

    return image;
}

QVector<uchar> ColorGradient::bits(uint length) const
{
    if (!isValid())
        return QVector<uchar>();
        
    QVector<uchar> bits;
    for (uint i = 0; i < length; ++i)
    {
        qreal position = (qreal)i / length;
        QColor color = interpolateColor(position);
        bits << color.red() << color.green() << color.blue() << color.alpha();
    }
    
    return bits;
}

QVector<qreal> ColorGradient::bitsF(uint length) const
{
    if (!isValid())
        return QVector<qreal>();
        
    QVector<qreal> bits;
    for (uint i = 0; i < length; ++i)
    {
        qreal position = (qreal)i / length;
        QColor color = interpolateColor(position);
        bits << color.redF() << color.greenF() << color.blueF() << color.alphaF();
    }
    
    return bits;
}

QColor ColorGradient::linearInterpolateColor(qreal position) const
{
    if (!isValid())
        return QColor();
    
    position = clamp(position, 0.0, 1.0);

    ColorGradientStops::const_iterator lowerBound, upperBound;
    upperBound = std::lower_bound(m_stops.begin(), 
                                  m_stops.end(), 
                                  ColorGradientStop(position));

    if (upperBound == m_stops.begin())
        return upperBound->color();

    if (upperBound == m_stops.end())
        return (--upperBound)->color();

    lowerBound = upperBound - 1;

    return lerpColor(*lowerBound, *upperBound, position);
}

bool ColorGradient::operator==(const ColorGradient & otherGradient) const
{
    return (m_type == otherGradient.m_type) && (m_stops == otherGradient.m_stops);
}

bool ColorGradient::operator!=(const ColorGradient & otherGradient) const
{
    return !(*this == otherGradient);
}

} // namespace widgetzeug
