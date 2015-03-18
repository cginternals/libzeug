#include "ColorGradientModel.h"

#include <algorithm>

#include <QImage>
#include <QVariant>

#include "ColorGradientStopModel.h"
#include "util.hpp"

namespace
{
    
bool lessThan(
    widgetzeug::ColorGradientStopModel * model1,
    widgetzeug::ColorGradientStopModel * model2)
{
    return model1->position() < model2->position();
}
    
} // namespace

namespace widgetzeug
{

ColorGradientModel::ColorGradientModel(const ColorGradient & gradient)
:   m_type{gradient.type()}
,   m_steps{gradient.steps()}
{
    for (const auto & stop : gradient.stops())
        newStop(stop);
        
    connect(this, &ColorGradientModel::stopsModified,
            this, &ColorGradientModel::changed);
}

ColorGradientModel::~ColorGradientModel() = default;

ColorGradientStopModel * ColorGradientModel::newStop(
    const ColorGradientStop & stop)
{
    auto model = new ColorGradientStopModel{stop, this};
    
    connect(model, &ColorGradientStopModel::changed,
            this, &ColorGradientModel::changed);
    
    connect(model, &ColorGradientStopModel::positionChanged,
        [this] ()
        {
            if (!std::is_sorted(m_stopModels.begin(), m_stopModels.end(), lessThan))
            {
                std::stable_sort(m_stopModels.begin(), m_stopModels.end(), lessThan);
                emit this->stopsModified();
            }
        });

    auto lowerBound = std::lower_bound(m_stopModels.begin(), m_stopModels.end(), model, lessThan);
    m_stopModels.insert(lowerBound, model);
    
    emit stopsModified();
    model->setCanRemove(canRemoveStop());
    updateCanRemove(true);
    return model;
}

bool ColorGradientModel::canRemoveStop() const
{
    return m_stopModels.count() > ColorGradient::s_minNumStops;
}

bool ColorGradientModel::removeStop(ColorGradientStopModel * model)
{
    auto it = std::find(m_stopModels.begin(), m_stopModels.end(), model);
    
    if (it == m_stopModels.end())
        return false;
    
    m_stopModels.erase(it);
    delete model;
    
    emit stopsModified();
    updateCanRemove(false);
    return true;
}

QList<ColorGradientStopModel *> ColorGradientModel::stopModels() const
{
    return m_stopModels;
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

void ColorGradientModel::setType(const QVariant & variant)
{
    using Gradient_underlying_type = std::underlying_type<widgetzeug::ColorGradientType>::type;

    m_type = static_cast<ColorGradientType>(variant.value<Gradient_underlying_type>());
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
    
    return ColorGradient{stops, m_type, m_steps};
}

void ColorGradientModel::updateCanRemove(bool more)
{
    if ((more && m_stopModels.count() == ColorGradient::s_minNumStops + 1)
        || (!more && m_stopModels.count() == ColorGradient::s_minNumStops))
    {
        for (auto stopModel : m_stopModels)
            stopModel->setCanRemove(canRemoveStop());
    }
}
    
} // namespace widgetzeug