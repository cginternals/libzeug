#include "ColorGradientLabel.h"

#include "ColorGradientModel.h"

namespace
{

const int g_margin = 6;

} // namespace

namespace widgetzeug
{

ColorGradientLabel::ColorGradientLabel(
    ColorGradientModel * model,
    QWidget * parent)
:   QLabel{parent}
,   m_model{model}
{
    setScaledContents(true);
    setMinimumSize(1, 30);
    setContentsMargins(g_margin, 0, g_margin, 0);
    
    update();

    connect(model, &ColorGradientModel::changed,
            this, &ColorGradientLabel::update);
}

void ColorGradientLabel::resizeEvent(QResizeEvent * event)
{
    update();
}

void ColorGradientLabel::update()
{
    auto image = m_model->image((width() - 2 * g_margin) * devicePixelRatio());
    auto pixmap = QPixmap::fromImage(image);
    pixmap.setDevicePixelRatio(devicePixelRatio());
    setPixmap(pixmap);
}

} // namespace widgetzeug