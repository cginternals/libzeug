#pragma once

#include <QPen>
#include <QColor>
#include <QWidget>

namespace widgetzeug
{

class ColorGradientStopModel;

class ColorGradientStopWidget : public QWidget
{
    Q_OBJECT

public:
    static const QSize s_size;

public:
    ColorGradientStopWidget(
        ColorGradientStopModel * model,
        QWidget * parent);
    
    void updatePosition();
    
    ColorGradientStopModel * model() const;
    
signals:
    void positionChanged(ColorGradientStopWidget * widget);
    void remove(ColorGradientStopWidget * widget);
    
protected:
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    void paintEvent(QPaintEvent * event) override;
    
protected:
    void initPainting();
    void drawShape(QPainter & painter);
    void drawColorRect(QPainter & painter);
    void drawCross(QPainter & painter);
    
    bool mousePosRemoves(const QPoint & mousePos);
    
private:
    ColorGradientStopModel * m_model;
    
    QPoint m_mousePos;
    QPoint m_initialPos;
    bool m_mouseMoved;
    bool m_pressed;
    bool m_remove;
    
    QPen m_shapePen;
    QBrush m_shapeBrush;
    QBrush m_pressedShapeBrush;
    QPainterPath m_shapePath;
    
    QRectF m_colorRect;
    
    QPen m_crossPen;
    QVector<QLineF> m_crossLines;
};

} // namespace widgetzeug