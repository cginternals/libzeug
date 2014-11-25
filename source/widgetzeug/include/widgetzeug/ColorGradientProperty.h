#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <reflectionzeug/Property.h>

#include <widgetzeug/ColorGradient.h>

namespace
{

std::string gradientToString(const widgetzeug::ColorGradient & gradient)
{
    QJsonObject jsonGradient;
    jsonGradient.insert("type", widgetzeug::ColorGradient::typeString(gradient.type()));

    QJsonArray stops;
    for (const widgetzeug::ColorGradientStop & stop : gradient.stops())
    {
        QJsonObject jsonStop;
        jsonStop.insert("color", stop.color().name(QColor::HexArgb));
        jsonStop.insert("position", stop.position());
        jsonStop.insert("midpoint", stop.midpoint());
        stops.append(jsonStop);
    }

    jsonGradient.insert("stops", stops);

    return QJsonDocument(jsonGradient).toJson(QJsonDocument::Compact).data();
}

bool gradientFromString(const std::string & string, widgetzeug::ColorGradient & gradient)
{
    QJsonDocument json = QJsonDocument::fromJson(QByteArray(string.c_str()));

    if (json.isNull() || json.isEmpty() || !json.isObject())
        return false;

    widgetzeug::ColorGradient newGradient;

    QJsonObject jsonGradient = json.object();

    QJsonValue value;
    if (!jsonGradient.contains("type") || !jsonGradient.value("type").isString())
        return false;

    static const QMap<QString, widgetzeug::ColorGradientType> types = {
        { "Discrete", widgetzeug::ColorGradientType::Discrete },
        { "Linear", widgetzeug::ColorGradientType::Linear },
        { "Matze", widgetzeug::ColorGradientType::Matze }
    };

    newGradient.setType(types.value(jsonGradient.value("type").toString()));

    if (!jsonGradient.contains("stops") || !jsonGradient.value("stops").isArray())
        return false;

    widgetzeug::ColorGradientStops stops;
    QJsonArray jsonStops = jsonGradient.value("stops").toArray();
    for (const QJsonValue & jsonStop : jsonStops)
    {
        if (!jsonStop.isObject())
            return false;

        QJsonObject stop = jsonStop.toObject();

        if (!stop.contains("color") ||
            !stop.value("color").isString() ||
            !stop.contains("position") ||
            !stop.value("position").isDouble())
            return false;

        QColor color;
        color.setNamedColor(stop.value("color").toString());

        qreal position = stop.value("position").toDouble();
        qreal midpoint = widgetzeug::ColorGradientStop::s_defaultMidpoint;

        if (stop.contains("midpoint") &&
            stop.value("midpoint").isDouble())
            midpoint = stop.value("midpoint").toDouble();

        stops.append(widgetzeug::ColorGradientStop(color, position, midpoint));
    }

    newGradient.setStops(stops);
    gradient = newGradient;
    return true;
}

}

namespace widgetzeug
{

class ColorGradientProperty : public reflectionzeug::ValueProperty<widgetzeug::ColorGradient>
{
public:
    using Type = widgetzeug::ColorGradient;

public:
    template <typename... Args>
    ColorGradientProperty(Args&&... args) : 
        ValueProperty<widgetzeug::ColorGradient>(std::forward<Args>(args)...) {}

    virtual std::string toString() const 
    {
        return gradientToString(this->value());
    }

    virtual bool fromString(const std::string & string)
    {
        widgetzeug::ColorGradient value;
        if (!gradientFromString(string, value))
            return false;

        this->setValue(value);
        return true;
    }
};

} // namespace

namespace reflectionzeug 
{

template <>
struct PropertyClass<widgetzeug::ColorGradient>
{
    using Type = widgetzeug::ColorGradientProperty;
};

} // namespace widgetzeug
