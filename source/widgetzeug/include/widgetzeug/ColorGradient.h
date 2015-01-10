#pragma once

#include <QList>
#include <QVector>

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/ColorGradientStop.h>

class QColor;
class QImage;

namespace widgetzeug
{

class ColorScheme;

using ColorGradientStops = QList<ColorGradientStop>;

enum class ColorGradientType : char { Linear, Discrete, Matze /* ToDo: rename :D */ }; 

class WIDGETZEUG_API ColorGradient
{
public:
    static const int s_minNumStops = 2;
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

	static QString typeString(const ColorGradientType type);

public:
	ColorGradient(
        ColorGradientType type = ColorGradientType::Linear,
        uint steps = s_defaultSteps);

    ColorGradient(
		const ColorGradientStops & stops, 
		ColorGradientType type = ColorGradientType::Linear,
        uint steps = s_defaultSteps);

    bool isValid() const;

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

private:
    QColor linearInterpolateColor(qreal position) const;
    
private:
    ColorGradientStops m_stops;
    ColorGradientType m_type;
    uint m_steps;
};

} // namespace widgetzeug
