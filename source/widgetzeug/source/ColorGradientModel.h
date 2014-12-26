#pragma once

#include <vector>

#include <QObject>

class QImage;

namespace widgetzeug
{

class ColorGradient;
class ColorGradientStop;
class ColorGradientStopModel;

class ColorGradientModel : public QObject
{
    Q_OBJECT

public:
    ColorGradientModel(const ColorGradient & gradient);
    ~ColorGradientModel();
    
    ColorGradientStopModel * newStop(const ColorGradientStop & stop);
    
    QList<ColorGradientStopModel *> stopModels() const;
    
    QColor interpolateColor(qreal position) const;
    QImage image(uint width) const;

    ColorGradient gradient() const;

signals:
    void changed();

private:
    std::vector<std::unique_ptr<ColorGradientStopModel>> m_stopModels;
};

} // namespace widgetzeug