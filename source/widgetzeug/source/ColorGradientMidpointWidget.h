#pragma once

#include <QPen>
#include <QWidget>

namespace widgetzeug
{

class ColorGradientStopModel;

class ColorGradientMidpointWidget : public QWidget
{
    Q_OBJECT

public:
    static const QSize s_size;

public:
    ColorGradientMidpointWidget(
        ColorGradientStopModel * mainModel,
        ColorGradientStopModel * nextModel,
        QWidget * parent);
    
    void updatePosition();
    
signals:
    void positionChanged();
    
protected:
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    void paintEvent(QPaintEvent * event) override;
    
private:
    void initPainting();
    
private:
    ColorGradientStopModel * m_mainModel;
    ColorGradientStopModel * m_nextModel;
    
    QPoint m_mousePos;
    bool m_pressed;
    
    QPen m_shapePen;
    QBrush m_shapeBrush;
    QBrush m_pressedShapeBrush;
    QPainterPath m_shapePath;
};

} // namespace widgetzeug