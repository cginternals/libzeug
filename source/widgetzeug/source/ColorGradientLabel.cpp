#include "ColorGradientLabel.h"

#include <QDebug>
#include <QPainter>
#include <QPaintEvent>

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
:   QOpenGLWidget{parent}
,   m_model{nullptr}
{
    setMinimumSize(1, 30);
    
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
    updatePixmap();
    
    connect(model, &ColorGradientModel::changed,
            this, &ColorGradientLabel::updatePixmap);
}

void ColorGradientLabel::resizeEvent(QResizeEvent * event)
{
    if (!m_model)
        return;
    
    updatePixmap();
}

void ColorGradientLabel::paintEvent(QPaintEvent * event)
{
    QPainter painter{this};
    painter.drawPixmap(event->rect(), m_pixmap, m_pixmap.rect());
}

void ColorGradientLabel::updatePixmap()
{
    auto image = m_model->image(width() * devicePixelRatio());
    m_pixmap = QPixmap::fromImage(image);
    
    update();
}

} // namespace widgetzeug