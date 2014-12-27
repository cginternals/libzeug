#pragma once

#include <memory>
#include <vector>

#include <QObject>

#include <widgetzeug/ColorGradient.h>

class QImage;

namespace widgetzeug
{

class ColorGradientStop;
class ColorGradientStopModel;

class ColorGradientModel : public QObject
{
    Q_OBJECT

public:
    ColorGradientModel(const ColorGradient & gradient);
    ~ColorGradientModel();
    
    ColorGradientStopModel * newStop(const ColorGradientStop & stop);
    bool removeStop(ColorGradientStopModel * model);
    QList<ColorGradientStopModel *> stopModels() const;
    
    ColorGradientType type() const;
    void setType(ColorGradientType type);
    
    uint steps() const;
    void setSteps(uint steps);
    
    QColor interpolateColor(qreal position) const;
    QImage image(uint width) const;

    ColorGradient gradient() const;

signals:
    void changed();
    void stopsModified();

private:
    std::vector<std::unique_ptr<ColorGradientStopModel>> m_stopModels;
    ColorGradientType m_type;
    uint m_steps;
};

} // namespace widgetzeug