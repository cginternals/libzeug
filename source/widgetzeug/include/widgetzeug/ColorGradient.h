#pragma once

#include <QList>
#include <QVector>

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/ColorGradientStop.h>

class QColor;
class QImage;
class QJsonObject;

namespace widgetzeug
{

class ColorScheme;

using ColorGradientStops = QList<ColorGradientStop>;

enum class ColorGradientType : char { Linear, Discrete, Cornsweet };


class WIDGETZEUG_API ColorGradient
{
public:
    static const auto s_defaultType = ColorGradientType::Linear;

    static const int s_minNumStops  = 2;
    static const int s_defaultSteps = 8;

    static ColorGradient fromScheme(
		ColorScheme * scheme, 
        int classes,
		ColorGradientType type = ColorGradientType::Linear,
        uint steps = s_defaultSteps);

    static ColorGradient fromList(
        const QList<QColor> & colors, 
        ColorGradientType type = ColorGradientType::Linear,
        uint steps = s_defaultSteps);
    
    static ColorGradient fromJson(const QJsonObject & jsonObject);

    static const QString typeString(ColorGradientType type);
    static ColorGradientType type(const QString & identifier);

    static const QVector<ColorGradientType> & types();

public:
	ColorGradient(
        ColorGradientType type = ColorGradientType::Linear,
        uint steps = s_defaultSteps);

    ColorGradient(
		const ColorGradientStops & stops, 
		ColorGradientType type = ColorGradientType::Linear,
        uint steps = s_defaultSteps);

    bool isValid() const;

    // ToDo: fix midpoint position on adding stops...

    void addStop(const ColorGradientStop & stop);
    void setStops(const ColorGradientStops & stops);
    ColorGradientStops stops() const;
    
    ColorGradientType type() const;
    void setType(ColorGradientType type);
    
    uint steps() const;
    void setSteps(uint steps);

    QColor interpolateColor(qreal position) const;
    
    QImage image(uint width = 256) const;
    QVector<uchar> bits(uint length) const;
    QVector<qreal> bitsF(uint length) const;
    
    bool operator==(const ColorGradient & rhs) const;
    bool operator!=(const ColorGradient & rhs) const;
    
    QJsonObject toJson() const;

private:
    QColor linearInterpolateColor(qreal position) const;
    
private:
    ColorGradientStops m_stops;
    ColorGradientType m_type;
    uint m_steps;
};

} // namespace widgetzeug
