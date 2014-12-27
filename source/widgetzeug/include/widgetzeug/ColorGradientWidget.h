#pragma once

#include <memory>

#include <QWidget>

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/ColorGradient.h>

class QLabel;

namespace widgetzeug
{

class ColorGradientLabel;
class ColorGradientMidpointBar;
class ColorGradientModel;
class ColorGradientStopBar;

class WIDGETZEUG_API ColorGradientWidget : public QWidget
{
public:
    ColorGradientWidget(
        const ColorGradient & gradient,
        QWidget * parent = nullptr);
    
    ~ColorGradientWidget();
    
    ColorGradient gradient() const;
    
private:
    std::unique_ptr<ColorGradientModel> m_model;
    
    ColorGradientMidpointBar * m_midpointBar;
    ColorGradientLabel * m_label;
    ColorGradientStopBar * m_bar;
};

} // namespace widgetzeug
