#include "ColorGradientStopWidget.h"

#include <cassert>

#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

#include "ColorGradientStopBar.h"
#include "util.hpp"

namespace widgetzeug
{

ColorGradientStopWidget::ColorGradientStopWidget(
    const QColor & color,
    qreal position,
    ColorGradientStopBar * bar)
:   QWidget{bar}
,   m_color{color}
,   m_position{clamp(position, 0.0, 1.0)}
,   m_pressed(false)
{
    assert(bar);
    
    setFixedSize(13, 15);
    setCursor(Qt::ArrowCursor);
    
    updatePosition();
    
    connect(bar, &ColorGradientStopBar::onResized,
            this, &ColorGradientStopWidget::updatePosition);
}

QColor ColorGradientStopWidget::color() const
{
    return m_color;
}

qreal ColorGradientStopWidget::position() const
{
    return m_position;
}

void ColorGradientStopWidget::mousePressEvent(QMouseEvent * event)
{
    m_initialPos = m_mousePos = event->globalPos();
    m_pressed = true;
    update();
}

void ColorGradientStopWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() != Qt::LeftButton)
        return;
    
    auto parentWidth = parentWidget()->width();
    
    auto newMousePos = event->globalPos();
    auto diff = newMousePos - m_mousePos;
    m_mousePos = newMousePos;
    auto newX = clamp(pos().x() + diff.x(), 0, parentWidth - width());
    
    m_position = static_cast<qreal>(newX) / (parentWidth - width());
    updatePosition();
    emit onPositionChanged(this);
}

void ColorGradientStopWidget::mouseReleaseEvent(QMouseEvent * event)
{
    m_pressed = false;
    update();
    
    if (m_initialPos != event->globalPos())
        return;
    
    m_color = QColorDialog::getColor(m_color, this);
    update();
    emit onColorChanged(this);
}

void ColorGradientStopWidget::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);
    
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    
    auto palette = this->palette();

    auto role = m_pressed ? QPalette::Midlight : QPalette::Light;
    painter.setBrush(palette.brush(QPalette::Active, role));
    
    auto pen = QPen{palette.color(QPalette::Active, QPalette::Dark)};
    pen.setWidthF(1.0);
    painter.setPen(pen);
    
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRoundedRect(1.0, 4.5, 11.0, 9.0, 2.0, 2.0);
    QVector<QPointF> top = { {6.5, 0.0}, {12.0, 6.0}, {1.0, 6.0} };
    path.addPolygon(top);
    
    painter.drawPath(path.simplified());
    
    painter.setBrush(m_color);
    painter.setPen(Qt::NoPen);
    
    painter.drawRect(QRectF{3.0, 7.0, 7.0, 4.0});
}

void ColorGradientStopWidget::updatePosition()
{
    move((parentWidget()->width() - width()) * m_position, 0);
}

} // namespace widgetzeug