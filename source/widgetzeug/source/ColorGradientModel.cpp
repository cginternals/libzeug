#include "ColorGradientModel.h"

#include <QDebug>
#include <QImage>

#include <widgetzeug/ColorGradient.h>
#include <widgetzeug/ColorGradientStop.h>

#include "ColorGradientStopModel.h"
#include "util.hpp"

namespace widgetzeug
{

ColorGradientModel::ColorGradientModel(const ColorGradient & gradient)
{
    for (const auto & stop : gradient.stops())
        newStop(stop);
}

ColorGradientModel::~ColorGradientModel() = default;

ColorGradientStopModel * ColorGradientModel::newStop(
    const ColorGradientStop & stop)
{
    auto model = make_unique<ColorGradientStopModel>(stop);
    
    connect(model.get(), &ColorGradientStopModel::changed,
            this, &ColorGradientModel::changed);
    
    auto rawPtr = model.get();
    m_stopModels.push_back(std::move(model));
    return rawPtr;
}

QList<ColorGradientStopModel *> ColorGradientModel::stopModels() const
{
    auto models = QList<ColorGradientStopModel *>{};
    
    for (auto & model : m_stopModels)
        models.append(model.get());
    
    return models;
}

QColor ColorGradientModel::interpolateColor(qreal position) const
{
    return gradient().interpolateColor(position);
}

QImage ColorGradientModel::image(uint width) const
{
    return gradient().image(width);
}

ColorGradient ColorGradientModel::gradient() const
{
    auto stops = ColorGradientStops{};
    
    for (auto & model : m_stopModels)
        stops.append(model->stop());
    
    return ColorGradient{stops};
}

} // namespace widgetzeug