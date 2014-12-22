#pragma once

#include <QGraphicsView>

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/ColorGradient.h>


namespace widgetzeug
{

class WIDGETZEUG_API ColorGradientWidget : public QGraphicsView
{
public:
    ColorGradientWidget(
        const ColorGradient & gradient,
        QWidget * parent = nullptr);
    
protected:
    void resizeEvent(QResizeEvent * event) override;

private:
    class Scene; friend Scene;
    Scene * m_scene;
};

} // namespace widgetzeug
