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
    return QJsonDocument(gradient.toJson()).toJson(QJsonDocument::Compact).data();
}

bool gradientFromString(const std::string & string, widgetzeug::ColorGradient & gradient)
{
    QJsonDocument json = QJsonDocument::fromJson(QByteArray(string.c_str()));

    if (json.isNull() || json.isEmpty() || !json.isObject())
        return false;

    gradient = widgetzeug::ColorGradient::fromJson(json.object());
    return gradient.isValid();
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
