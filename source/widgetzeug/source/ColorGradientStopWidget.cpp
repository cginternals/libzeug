#include "ColorGradientStopWidget.h"

#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

#include "ColorGradientStopModel.h"
#include "ColorGradientStopBar.h"
#include "util.hpp"

namespace widgetzeug
{

ColorGradientStopWidget::ColorGradientStopWidget(
    ColorGradientStopModel * model,
    ColorGradientStopBar * bar)
:   QWidget{bar}
,   m_model{model}
,   m_pressed{false}
,   m_remove{false}
{
    setFixedSize(13, 15);
    setCursor(Qt::ArrowCursor);
    
    updatePosition();
    
    connect(bar, &ColorGradientStopBar::resized,
            this, &ColorGradientStopWidget::updatePosition);
}

ColorGradientStopModel * ColorGradientStopWidget::model() const
{
    return m_model;
}

void ColorGradientStopWidget::mousePressEvent(QMouseEvent * event)
{
    if (event->buttons() != Qt::LeftButton)
        return;
    
    m_initialPos = m_mousePos = event->globalPos();
    m_pressed = true;
    m_remove = false;
    update();
}

void ColorGradientStopWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() != Qt::LeftButton)
        return;
        
    if (qAbs(m_initialPos.y() - event->globalPos().y()) > 50)
    {
        m_remove = true;
        update();
        return;
    }
    
    m_remove = false;
    
    auto parentWidth = parentWidget()->width();
    
    auto newMousePos = event->globalPos();
    auto diff = newMousePos - m_mousePos;
    m_mousePos = newMousePos;
    auto newX = clamp(pos().x() + diff.x(), 0, parentWidth - width());
    
    m_model->setPosition(static_cast<qreal>(newX) / (parentWidth - width()));
    updatePosition();
    emit positionChanged(this);
}

void ColorGradientStopWidget::mouseReleaseEvent(QMouseEvent * event)
{
    m_pressed = false;
    m_remove = false;
    update();
    
    if (m_initialPos == event->globalPos())
    {
        m_model->setColor(QColorDialog::getColor(
            m_model->color(),
            this,
            QString{},
            QColorDialog::ShowAlphaChannel));
        
        update();
        return;
    }
    
    if (qAbs(m_initialPos.y() - event->globalPos().y()) > 50)
    {
        emit remove(this);
    }
}

void ColorGradientStopWidget::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);
    
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    
    auto palette = this->palette();

    auto role = m_pressed ? QPalette::Dark : QPalette::Light;
    painter.setBrush(palette.brush(QPalette::Active, role));
    
    auto pen = QPen{palette.color(QPalette::Mid)};
    pen.setWidthF(1.0);
    painter.setPen(pen);
    
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRoundedRect(0.5, 4.5, 12, 9.0, 2.0, 2.0);
    QVector<QPointF> top = { {6.5, 0.0}, {12.0, 5.5}, {1.0, 5.5} };
    path.addPolygon(top);
    
    painter.drawPath(path.simplified());
    
    if (!m_remove)
    {
        painter.setBrush(m_model->color());
        painter.setPen(Qt::NoPen);
        painter.drawRect(QRectF{3.0, 7.0, 7.0, 4.0});
    }
    else
    {
        pen.setWidthF(2);
        pen.setColor(palette.color(QPalette::Text));
        painter.setPen(pen);
        painter.drawLines(QVector<QLineF>{{4.5, 6.5, 8.5, 10.5}, {8.5, 6.5, 4.5, 10.5}});
    }
}

void ColorGradientStopWidget::updatePosition()
{
    move((parentWidget()->width() - width()) * m_model->position(), 0);
}

} // namespace widgetzeug