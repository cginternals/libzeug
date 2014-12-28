#include "ColorGradientLabel.h"

#include "ColorGradientModel.h"

namespace
{

const QBrush TransparencyBackgroundBrush()
{
    const int size = 12;
    QImage backgroundImage(size, size, QImage::Format_ARGB32);
    unsigned char *bits = backgroundImage.bits();
    
    int color, i;
    for(unsigned short x = 0; x < size; ++x)
        for(unsigned short y = 0; y < size; ++y)
        {
            i = (x * size + y) * 4;
            
            color = (x <= 5 && y <= 5) || (x > 5 && y > 5) ? 255 : 224;
            
            bits[i + 2] = color;
            bits[i + 1] = color;
            bits[i + 0] = color;
            bits[i + 3] = 255;
        }
    
    return QBrush(backgroundImage);
};

} // namespace

namespace widgetzeug
{

ColorGradientLabel::ColorGradientLabel(QWidget * parent)
:   QLabel{parent}
,   m_model{nullptr}
{
    setScaledContents(true);
    setMinimumSize(1, 30);
    setContentsMargins(0, 0, 0, 0);
    
    auto palette = QPalette{};
    palette.setBrush(QPalette::Background, QBrush(TransparencyBackgroundBrush()));
    
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Background);
    setPalette(palette);
}

ColorGradientLabel::ColorGradientLabel(
    ColorGradientModel * model,
    QWidget * parent)
:   ColorGradientLabel{parent}
{
    setModel(model);
}

void ColorGradientLabel::setModel(widgetzeug::ColorGradientModel * model)
{
    if (m_model)
        m_model->disconnect(this);
    
    m_model = model;
    update();
    connect(model, &ColorGradientModel::changed,
            this, &ColorGradientLabel::update);
}

void ColorGradientLabel::resizeEvent(QResizeEvent * event)
{
    if (!m_model)
        return;
    
    update();
}

void ColorGradientLabel::update()
{
    auto image = m_model->image(width() * devicePixelRatio());
    auto pixmap = QPixmap::fromImage(image);
    pixmap.setDevicePixelRatio(devicePixelRatio());
    setPixmap(pixmap);
}

} // namespace widgetzeug