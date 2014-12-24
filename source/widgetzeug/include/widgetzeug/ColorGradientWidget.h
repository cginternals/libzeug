#pragma once

#include <QWidget>

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/ColorGradient.h>

class QLabel;

namespace widgetzeug
{

class ColorGradientStopBar;

class WIDGETZEUG_API ColorGradientWidget : public QWidget
{
public:
    ColorGradientWidget(
        const ColorGradient & gradient,
        QWidget * parent = nullptr);
    
protected:
    void resizeEvent(QResizeEvent * event) override;
    
protected:
    void stopsChanged();
    
private:
    QLabel * m_gradientLabel;
    ColorGradientStopBar * m_bar;
};

} // namespace widgetzeug
