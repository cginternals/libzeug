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
    
    initPainting();
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
    update();
    
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
        auto newColor = QColorDialog::getColor(
            m_model->color(),
            this,
            QString{},
            QColorDialog::ShowAlphaChannel);
        
        if (!newColor.isValid())
            return;
        
        m_model->setColor(newColor);
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
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);

    drawShape(painter);
    
    if (!m_remove)
        drawColorRect(painter);
    else
        drawCross(painter);
}

void ColorGradientStopWidget::updatePosition()
{
    move((parentWidget()->width() - width()) * m_model->position(), 0);
}

void ColorGradientStopWidget::initPainting()
{
    auto palette = this->palette();
    
    m_shapePen = QPen{palette.color(QPalette::Mid)};
    m_shapePen.setWidthF(1.0);
    
    m_shapeBrush = palette.brush(QPalette::Active, QPalette::Light);
    m_pressedShapeBrush = palette.brush(QPalette::Active, QPalette::Dark);
    
    auto painterPath = QPainterPath{};
    painterPath.setFillRule(Qt::WindingFill);
    painterPath.addRoundedRect(0.5, 4.5, 12, 9.0, 2.0, 2.0);
    QVector<QPointF> tip = { {6.5, 0.0}, {12.0, 5.5}, {1.0, 5.5} };
    painterPath.addPolygon(tip);
    
    m_shapePath = painterPath.simplified();
    
    m_colorRect = QRectF{3.0, 7.0, 7.0, 4.0};
    
    m_crossPen = QPen(palette.color(QPalette::Text));
    m_crossPen.setWidthF(2.0);
    m_crossLines = QVector<QLineF>{{4.5, 6.5, 8.5, 10.5}, {8.5, 6.5, 4.5, 10.5}};
}

void ColorGradientStopWidget::drawShape(QPainter & painter)
{
    painter.setPen(m_shapePen);
    painter.setBrush(m_pressed ? m_pressedShapeBrush : m_shapeBrush);
    painter.drawPath(m_shapePath);
}

void ColorGradientStopWidget::drawColorRect(QPainter & painter)
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_model->color());
    painter.drawRect(m_colorRect);
}

void ColorGradientStopWidget::drawCross(QPainter & painter)
{
    painter.setPen(m_crossPen);
    painter.drawLines(m_crossLines);
}

} // namespace widgetzeug