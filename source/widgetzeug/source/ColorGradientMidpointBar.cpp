#include "ColorGradientMidpointBar.h"

#include <algorithm>

#include <QResizeEvent>

#include "ColorGradientModel.h"
#include "ColorGradientStopModel.h"
#include "ColorGradientMidpointWidget.h"
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

ColorGradientMidpointBar::ColorGradientMidpointBar(
    ColorGradientModel * model,
    QWidget * parent)
:   QWidget{parent}
,   m_model{model}
{
    setMinimumWidth(100);
    setFixedHeight(12);
    
    initMidpoints();
    
    connect(model, &ColorGradientModel::stopsModified,
            this, &ColorGradientMidpointBar::initMidpoints);
}

ColorGradientMidpointBar::~ColorGradientMidpointBar() = default;

void ColorGradientMidpointBar::resizeEvent(QResizeEvent * event)
{
    emit resized(event->size());
}

void ColorGradientMidpointBar::initMidpoints()
{
    clearMidpoints();
    
    auto stopModels = m_model->stopModels();
    std::stable_sort(stopModels.begin(), stopModels.end(), lessThan);
    
    auto it = stopModels.begin();
    while (it != stopModels.end())
    {
        auto previous = it++;
        
        if (it == stopModels.end())
            break;
        
        auto mainModel = *previous;
        auto nextModel = *it;
        
        auto widget = new ColorGradientMidpointWidget{mainModel, nextModel, this};
        widget->show();
        
        connect(this, &ColorGradientMidpointBar::resized,
                widget, &ColorGradientMidpointWidget::updatePosition);
        
        m_stopWidgets.append(widget);
    }
}

void ColorGradientMidpointBar::clearMidpoints()
{
    qDeleteAll(m_stopWidgets);
    m_stopWidgets.clear();
}

} // namespace widgetzeug