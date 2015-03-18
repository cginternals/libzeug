#pragma once

#include <QList>
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
    bool canRemoveStop() const;
    bool removeStop(ColorGradientStopModel * model);
    QList<ColorGradientStopModel *> stopModels() const;
    
    ColorGradientType type() const;
    void setType(ColorGradientType type);
    void setType(const QVariant & variant);
    
    uint steps() const;
    void setSteps(uint steps);
    
    QColor interpolateColor(qreal position) const;
    QImage image(uint width) const;

    ColorGradient gradient() const;

signals:
    void changed();
    void stopsModified();
    
private:
    void updateCanRemove(bool more);

private:
    QList<ColorGradientStopModel *> m_stopModels;
    ColorGradientType m_type;
    uint m_steps;
};

} // namespace widgetzeug