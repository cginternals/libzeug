#include "ColorGradientStopWidget.h"

#include <QColorDialog>
#include <QMouseEvent>
#include <QMoveEvent>
#include <QPainter>
#include <QPainterPath>
#include <QStyle>
#include <QToolTip>

#include "ColorGradientStopModel.h"
#include "util.hpp"

class MyWidget : public QWidget
{
public:
    MyWidget()
    {
        setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
        //    widget2.setAttribute(Qt::WA_NoSystemBackground, true);
        setAttribute(Qt::WA_TranslucentBackground, true);
        //    widget2.setAttribute(Qt::WA_PaintOnScreen);
        
        auto font = this->font();
        font.setPointSizeF(10.0);
        setFont(font);
    }

    MyWidget(const QString & text)
    :   MyWidget{}
    {
        setText(text);
    }
    
    void setText(const QString & text)
    {
        m_text = text;
        
        auto boundingRect = fontMetrics().boundingRect(m_text);
        auto newWidth = boundingRect.width();
        if (newWidth + 20 != width())
            setFixedSize(boundingRect.width() + 20, 23);
        update();
    }
    
    void moveTip(const QPoint & position)
    {
        const auto tipPos = QPoint{width() / 2, height()};
        move(position - tipPos);
    }
    
    void paintEvent(QPaintEvent * event) override
    {
        QPainter painter{this};
        painter.setRenderHints(QPainter::Antialiasing);
        
        painter.save();
        
        auto shapeBrush = palette().brush(QPalette::Active, QPalette::Light);
        painter.setBrush(shapeBrush);
        painter.setPen(Qt::NoPen);
        
        painter.drawPath(shape());
        painter.restore();
        
        style()->drawItemText(
            &painter,
            QRect{0, 0, width(), 18},
            Qt::AlignVCenter | Qt::AlignHCenter,
            palette(),
            true,
            m_text);
    }
    
private:
    QPainterPath shape()
    {
        auto path = QPainterPath{};
        path.setFillRule(Qt::WindingFill);
        
        const auto tipPos = QPointF{width() / 2.0, static_cast<qreal>(height())};
        
        path.addRoundedRect(QRectF{0.0, 0.0, static_cast<qreal>(width()), 18.0}, 9.0, 9.0);
        path.addPolygon(QVector<QPointF>{ {tipPos.x() - 3.0, 18.0}, {tipPos.x() + 3.0, 18.0}, tipPos });
        return path;
    }
    
private:
    QString m_text;
};

namespace widgetzeug
{

const QSize ColorGradientStopWidget::s_size = {13, 16};

ColorGradientStopWidget::ColorGradientStopWidget(
    ColorGradientStopModel * model,
    QWidget * parent)
:   QWidget{parent}
,   m_model{model}
,   m_mouseMoved{false}
,   m_pressed{false}
,   m_remove{false}
,   m_tooltip{new MyWidget{}}
{
    setFixedSize(s_size);
    setCursor(Qt::ArrowCursor);
    
    initPainting();
    updatePosition();
}

void ColorGradientStopWidget::updatePosition()
{
    move(qRound((parentWidget()->width() - width()) * m_model->position()), 0);
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
    m_mouseMoved = false;
    m_tooltip->show();
    update();
}

void ColorGradientStopWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() != Qt::LeftButton)
        return;
    
    const auto newMousePos = event->globalPos();
    m_mouseMoved = true;
    
    if (mousePosRemoves(newMousePos))
    {
        if (!m_remove)
        {
            m_remove = true;
            update();
        }
        return;
    }
    
    if (m_remove)
    {
        m_remove = false;
        update();
    }
    
    const auto parentWidth = parentWidget()->width();
    const auto diff = newMousePos - m_mousePos;
    const auto newX = pos().x() + diff.x();
    
    m_mousePos = newMousePos;
    m_model->setPosition(static_cast<qreal>(newX) / (parentWidth - width()));
    
    updatePosition();
    emit positionChanged(this);
    
    m_tooltip->setText(QString{"%1%"}.arg(qRound(m_model->position() * 100)));
}

void ColorGradientStopWidget::mouseReleaseEvent(QMouseEvent * event)
{
    const auto newMousePos = event->globalPos();
    m_pressed = false;
    m_remove = false;
    update();
    
    m_tooltip->hide();
    
    if (!m_mouseMoved)
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
    
    if (mousePosRemoves(newMousePos))
    {
        emit remove(this);
        return;
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

void ColorGradientStopWidget::moveEvent(QMoveEvent * event)
{
    m_tooltip->moveTip(mapToGlobal({6, -4}));
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
    painterPath.addRoundedRect(0.5, 5.0, 12, 10.5, 2.0, 2.0);
    QVector<QPointF> tip = { {6.5, 0.0}, {12.0, 5.7}, {1.0, 5.7} };
    painterPath.addPolygon(tip);
    
    m_shapePath = painterPath.simplified();
    
    m_colorRect = QRectF{3.0, 7.0, 7.0, 6.0};
    
    m_crossPen = QPen(palette.color(QPalette::Text));
    m_crossPen.setWidthF(2.0);
    m_crossLines = QVector<QLineF>{{4.5, 8.0, 8.5, 12.0}, {8.5, 8.0, 4.5, 12.0}};
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
    auto color = m_model->color();
    color.setAlpha(255);
    painter.setBrush(color);
    painter.drawRect(m_colorRect);
}

void ColorGradientStopWidget::drawCross(QPainter & painter)
{
    painter.setPen(m_crossPen);
    painter.drawLines(m_crossLines);
}

bool ColorGradientStopWidget::mousePosRemoves(const QPoint & mousePos)
{
    return qAbs(m_initialPos.y() - mousePos.y()) > 30 && m_model->canRemove();
}

} // namespace widgetzeug