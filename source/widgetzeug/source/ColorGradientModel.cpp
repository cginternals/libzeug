#include "ColorGradientModel.h"

#include <QDebug>
#include <QImage>

#include "ColorGradientStopModel.h"
#include "util.hpp"

namespace widgetzeug
{

ColorGradientModel::ColorGradientModel(const ColorGradient & gradient)
:   m_type{gradient.type()}
,   m_steps{12}
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
    emit stopsModified();
    return rawPtr;
}

bool ColorGradientModel::removeStop(ColorGradientStopModel * model)
{
    auto it = std::find_if(m_stopModels.begin(), m_stopModels.end(),
        [model] (const std::unique_ptr<ColorGradientStopModel> & stopModel)
        {
            return stopModel.get() == model;
        });
    
    if (it == m_stopModels.end())
        return false;
    
    m_stopModels.erase(it);
    emit changed();
    emit stopsModified();
    return true;
}

QList<ColorGradientStopModel *> ColorGradientModel::stopModels() const
{
    auto models = QList<ColorGradientStopModel *>{};
    
    for (auto & model : m_stopModels)
        models.append(model.get());
    
    return models;
}

ColorGradientType ColorGradientModel::type() const
{
    return m_type;
}

void ColorGradientModel::setType(ColorGradientType type)
{
    m_type = type;
    emit changed();
}

uint ColorGradientModel::steps() const
{
    return m_steps;
}

void ColorGradientModel::setSteps(uint steps)
{
    m_steps = steps;
    changed();
}

QColor ColorGradientModel::interpolateColor(qreal position) const
{
    return gradient().interpolateColor(position, m_steps);
}

QImage ColorGradientModel::image(uint width) const
{
    return gradient().image(width, m_steps);
}

ColorGradient ColorGradientModel::gradient() const
{
    auto stops = ColorGradientStops{};
    
    for (auto & model : m_stopModels)
        stops.append(model->stop());
    
    return ColorGradient{stops, m_type};
}

} // namespace widgetzeug