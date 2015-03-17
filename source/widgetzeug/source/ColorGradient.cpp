#include <widgetzeug/ColorGradient.h>

#include <algorithm>

#include <QDebug>
#include <QImage>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector4D>

#include <widgetzeug/ColorScheme.h>

#include "util.hpp"

namespace widgetzeug
{

namespace 
{

QColor lerpColor(const ColorGradientStop & stop1, const ColorGradientStop & stop2, qreal position)
{
    const auto pos = (position - stop1.position()) / (stop2.position() - stop1.position());
    const auto midpoint = stop1.midpoint();

    const auto color1 = stop1.color();
    const auto color2 = stop2.color();

    const auto vec1 = QVector4D(color1.redF(), color1.greenF(), color1.blueF(), color1.alphaF());
    const auto vec2 = QVector4D(color2.redF(), color2.greenF(), color2.blueF(), color2.alphaF());
    
    const auto avg = QVector4D{(vec1 + vec2) / 2.0f};
    
    auto result = QVector4D{};
    if (pos > midpoint)
        result = mix(avg, vec2, (pos - midpoint) / (1.0f - midpoint));
    else
        result = mix(vec1, avg,  pos / midpoint);

    return QColor::fromRgbF(result.x(), result.y(), result.z(), result.w());
}

QColor makeLighter(const QColor & color, qreal factor)
{
    if (factor == 1.0)
        return color;
    
    auto hueF = 0.0, saturationF = 0.0, valueF = 0.0, alphaF = 0.0;
    color.getHsvF(&hueF, &saturationF, &valueF, &alphaF);
    valueF = clamp(valueF * factor, 0.0, 1.0);
    return QColor::fromHsvF(hueF, saturationF, valueF, alphaF);
}

} // namespace


const QString ColorGradient::typeString(ColorGradientType type)
{
    static const QMap<ColorGradientType, QString> identifiersByType = {
        { ColorGradientType::Cornsweet, "Cornsweet" },
        { ColorGradientType::Discrete,  "Discrete" },
        { ColorGradientType::Linear,    "Linear" } };

    return identifiersByType.value(type);
}

ColorGradientType ColorGradient::type(const QString & identifier)
{
    static const QMap<QString, ColorGradientType> typesIdentifier = {
        { "Cornsweet", ColorGradientType::Cornsweet},
        { "Discrete", ColorGradientType::Discrete },
        { "Linear", ColorGradientType::Linear } };

    return typesIdentifier.value(identifier);
}

const QVector<ColorGradientType> & ColorGradient::types()
{
    static const QVector<ColorGradientType> types = {
        ColorGradientType::Cornsweet, 
        ColorGradientType::Discrete,
        ColorGradientType::Linear };

    return types;
}

//ColorGradient ColorGradient::fromScheme(
//    ColorScheme * scheme, 
//    uint classes, 
//    ColorGradientType type,
//    uint steps)
//{
//    if (classes > scheme->maxClasses() || classes < scheme->minClasses())
//        return ColorGradient();
//
//    return fromList(scheme->colors(classes), type, steps);
//}

//ColorGradient ColorGradient::fromList(
//    const QList<QColor> & colors,
//    ColorGradientType type,
//    uint steps)
//{
//    if (colors.count() < s_minNumStops)
//        return ColorGradient();
//
//    auto gradient = ColorGradient{type, steps};
//
//    const auto dimension = 1.0 / (colors.count() - 1);
//
//    for (auto i = 0; i < colors.size(); ++i)
//        gradient.addStop(ColorGradientStop(colors[i], dimension * i));
//
//    return gradient;
//}

ColorGradient ColorGradient::fromJson(const QJsonObject & jsonObject)
{
    if (jsonObject.isEmpty())
        return {};
    
    auto gradient = ColorGradient{};
    
    auto value = QJsonValue{};
    
    if (!jsonObject.contains("type") || !jsonObject.value("type").isString())
        gradient.setType(s_defaultType);
    else
        gradient.setType(type(jsonObject.value("type").toString()));

    if (!jsonObject.contains("steps") || !jsonObject.value("steps").isDouble())
        gradient.setSteps(s_defaultSteps);
    else
        gradient.setSteps(jsonObject.value("steps").toDouble());
    
    if (!jsonObject.contains("stops") || !jsonObject.value("stops").isArray())
        return {};
    
    auto stops = ColorGradientStops{};
    auto jsonStops = jsonObject.value("stops").toArray();
    for (const QJsonValue & jsonStop : jsonStops)
    {
        if (!jsonStop.isObject())
            return {};
        
        auto stop = jsonStop.toObject();
        
        if (!stop.contains("color") ||
            !stop.value("color").isString() ||
            !stop.contains("position") ||
            !stop.value("position").isDouble())
            return {};
        
        auto color = QColor{};
        color.setNamedColor(stop.value("color").toString());
        
        const auto position = stop.value("position").toDouble();
        auto midpoint = ColorGradientStop::s_defaultMidpoint;
        
        if (stop.contains("midpoint") &&
            stop.value("midpoint").isDouble())
            midpoint = stop.value("midpoint").toDouble();
        
        stops.append(ColorGradientStop{color, position, midpoint});
    }
    
    gradient.setStops(stops);
    return gradient;
}


ColorGradient::ColorGradient(ColorGradientType type, uint steps)
:   ColorGradient{ColorGradientStops(), type, steps}
{
}

ColorGradient::ColorGradient(
    const ColorGradientStops & stops, 
    ColorGradientType type,
    uint steps)
:   m_type{type}
,   m_steps{steps}
{
    setStops(stops);
}

bool ColorGradient::isValid() const
{
    return m_stops.count() >= s_minNumStops;
}

void ColorGradient::addStop(const ColorGradientStop & stop)
{
    const auto it = std::lower_bound(m_stops.begin(), m_stops.end(), stop);
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

// ToDo: rename interpolate
// ToDo: reduce use of magic numbers
// ToDo: refine cornsweet

QColor ColorGradient::interpolateColor(qreal position) const
{
    if (m_type == ColorGradientType::Linear)
        return linearInterpolateColor(position);
        
    if (!isValid())
        return QColor();
            
    auto discretePosition = std::floor(position * m_steps) / m_steps;
    discretePosition *= 1.0 + 1.0 / (m_steps - 1);
    
    if (m_type == ColorGradientType::Discrete)
        return linearInterpolateColor(discretePosition);
    
    static const auto maxLighteningFactor = 0.4;
    static const auto percentage = 0.2;
    const auto discreteColor = linearInterpolateColor(discretePosition);
    const auto positionInsideStep = fract(position * m_steps);
    
    auto lighteningFactor = 1.0;
    if (positionInsideStep >= (1.0 - percentage))
    {
        const auto positionEdge = (positionInsideStep - (1.0 - percentage)) / percentage;
        lighteningFactor = 1.0 - std::pow(positionEdge, 3.0) * maxLighteningFactor;
    }
    else if (positionInsideStep <= percentage)
    {
        const auto positionEdge = 1.0 - positionInsideStep / percentage;
        lighteningFactor = 1.0 + std::pow(positionEdge, 3.0) * maxLighteningFactor;
    }
    
    return makeLighter(discreteColor, lighteningFactor);
}

QImage ColorGradient::image(uint width) const
{
    if (!isValid())
        return QImage();

    auto image = QImage{static_cast<int>(width), 1, QImage::Format_ARGB32};

    for (auto i = 0u; i < width; ++i)
    {
        const auto position = static_cast<qreal>(i) / width;
        image.setPixel(i, 0, interpolateColor(position).rgba());
    }

    return image;
}

QVector<uchar> ColorGradient::bits(uint length) const
{
    if (!isValid())
        return QVector<uchar>();
        
    auto bits = QVector<uchar>{};
    for (auto i = 0u; i < length; ++i)
    {
        const auto position = static_cast<qreal>(i) / length;
        const auto color = interpolateColor(position);
        bits << color.red() << color.green() << color.blue() << color.alpha();
    }
    
    return bits;
}

QVector<qreal> ColorGradient::bitsF(uint length) const
{
    if (!isValid())
        return QVector<qreal>();
        
    auto bits = QVector<qreal>{};
    for (auto i = 0u; i < length; ++i)
    {
        qreal position = (qreal)i / length;
        auto color = interpolateColor(position);
        bits << color.redF() << color.greenF() << color.blueF() << color.alphaF();
    }
    
    return bits;
}

QColor ColorGradient::linearInterpolateColor(qreal position) const
{
    if (!isValid())
        return QColor();
    
    position = clamp(position, 0.0, 1.0);

    auto upperBound = std::lower_bound(
        m_stops.begin(),
        m_stops.end(),
        ColorGradientStop(position));

    if (upperBound == m_stops.begin())
        return upperBound->color();

    if (upperBound == m_stops.end())
        return (--upperBound)->color();

    const auto lowerBound = upperBound - 1;

    return lerpColor(*lowerBound, *upperBound, position);
}

bool ColorGradient::operator==(const ColorGradient & rhs) const
{
    return (m_type == rhs.m_type) && (m_stops == rhs.m_stops);
}

bool ColorGradient::operator!=(const ColorGradient & rhs) const
{
    return !(*this == rhs);
}

QJsonObject ColorGradient::toJson() const
{
    auto jsonGradient = QJsonObject{};
    jsonGradient.insert("type", typeString(m_type));
    
    if (m_type != ColorGradientType::Linear)
        jsonGradient.insert("steps", static_cast<int>(m_steps));
    
    auto stops = QJsonArray{};
    for (const widgetzeug::ColorGradientStop & stop : m_stops)
    {
        auto jsonStop = QJsonObject{};
        jsonStop.insert("color", stop.color().name(QColor::HexArgb));
        jsonStop.insert("position", stop.position());
        jsonStop.insert("midpoint", stop.midpoint());
        stops.append(jsonStop);
    }
    
    jsonGradient.insert("stops", stops);
    return jsonGradient;
}

} // namespace widgetzeug
