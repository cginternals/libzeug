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

    static ColorGradient fromScheme(
		ColorScheme * scheme, 
        int classes,
		ColorGradientType type = ColorGradientType::Linear);

    static ColorGradient fromList(
        const QList<QColor> & colors, 
        ColorGradientType type = ColorGradientType::Linear);

	static const QString typeString(const ColorGradientType type);

public:
	ColorGradient(ColorGradientType type = ColorGradientType::Linear);

    ColorGradient(
		const ColorGradientStops & stops, 
		ColorGradientType type = ColorGradientType::Linear);

    bool isValid() const;

    void addStop(const ColorGradientStop & stop);
    void setStops(const ColorGradientStops & stops);
    ColorGradientStops stops() const;
    
    ColorGradientType type() const;
    void setType(ColorGradientType type);
    
    QColor interpolateColor(qreal position, uint steps = 0) const;
    
    QImage image(uint width = 256, uint steps = 0) const;
    QVector<uchar> bits(uint length, uint steps = 0) const;
    QVector<qreal> bitsF(uint length, uint steps = 0) const;
    
    bool operator==(const ColorGradient & otherGradient) const;
    bool operator!=(const ColorGradient & otherGradient) const;

private:
    QColor linearInterpolateColor(qreal position) const;
    
private:
    ColorGradientStops m_stops;
    ColorGradientType m_type;
};

} // namespace widgetzeug
