#include "ColorGradientMidpointWidget.h"

#include <QMouseEvent>
#include <QPainter>

#include "ColorGradientStopModel.h"
#include "util.hpp"

namespace widgetzeug
{

const QSize ColorGradientMidpointWidget::s_size = {9, 12};

ColorGradientMidpointWidget::ColorGradientMidpointWidget(
    ColorGradientStopModel * mainModel,
    ColorGradientStopModel * nextModel,
    QWidget * parent)
:   QWidget{parent}
,   m_mainModel{mainModel}
,   m_nextModel{nextModel}
,   m_pressed{false}
{
    setFixedSize(s_size);
    
    initPainting();
    updatePosition();
    
    connect(m_mainModel, &ColorGradientStopModel::changed,
            this, &ColorGradientMidpointWidget::updatePosition);
    
    connect(m_nextModel, &ColorGradientStopModel::changed,
            this, &ColorGradientMidpointWidget::updatePosition);
}

void ColorGradientMidpointWidget::updatePosition()
{
    const auto leftStop = m_mainModel->position();
    const auto rightStop = m_nextModel->position();
    const auto absolutePos = leftStop + (rightStop - leftStop) * m_mainModel->midpoint();
    move(qRound((parentWidget()->width() - width()) * absolutePos), 0);
}
    
void ColorGradientMidpointWidget::mousePressEvent(QMouseEvent * event)
{
    if (event->buttons() != Qt::LeftButton)
        return;
    
    m_mousePos = event->globalPos();
    m_pressed = true;
    update();
}

void ColorGradientMidpointWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() != Qt::LeftButton)
        return;
    
    const auto newMousePos = event->globalPos();
    
    const auto parentWidth = parentWidget()->width();
    const auto diff = newMousePos - m_mousePos;
    const auto newX = pos().x() + diff.x();
    
    const auto absolutePos = static_cast<qreal>(newX) / (parentWidth - width());
    const auto leftStop = m_mainModel->position();
    const auto rightStop = m_nextModel->position();
    auto midpoint = (absolutePos - leftStop) / (rightStop - leftStop);
    m_mainModel->setMidpoint(midpoint);
    m_mousePos = newMousePos;
    updatePosition();
}

void ColorGradientMidpointWidget::mouseReleaseEvent(QMouseEvent * event)
{
    m_pressed = false;
    update();
}

void ColorGradientMidpointWidget::paintEvent(QPaintEvent * event)
{
    QPainter painter{this};
    painter.setRenderHints(QPainter::Antialiasing);
    
    painter.setPen(m_shapePen);
    painter.setBrush(m_pressed ? m_pressedShapeBrush : m_shapeBrush);
    painter.drawPath(m_shapePath);
}

void ColorGradientMidpointWidget::initPainting()
{
    auto palette = this->palette();
    
    m_shapePen = QPen{palette.color(QPalette::Mid)};
    m_shapePen.setWidthF(1.0);
    
    m_shapeBrush = palette.brush(QPalette::Active, QPalette::Light);
    m_pressedShapeBrush = palette.brush(QPalette::Active, QPalette::Dark);
    
    auto painterPath = QPainterPath{};
    painterPath.setFillRule(Qt::WindingFill);
    painterPath.addRoundedRect(0.5, 0.5, 8.0, 7.0, 2.0, 2.0);
    QVector<QPointF> tip = { {4.5, 11.0}, {0.5, 6.0}, {8.5, 6.0} };
    painterPath.addPolygon(tip);
    
    m_shapePath = painterPath.simplified();
}

} // namespace widgetzeug
