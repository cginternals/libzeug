#pragma once

#include <QColor>
#include <QWidget>

namespace widgetzeug
{

class ColorGradientStopBar;

class ColorGradientStopWidget : public QWidget
{
    Q_OBJECT

public:
    ColorGradientStopWidget(
        const QColor & color,
        qreal position,
        ColorGradientStopBar * bar);
    
    QColor color() const;
    qreal position() const;
    
signals:
    void onPositionChanged(ColorGradientStopWidget * widget);
    void onColorChanged(ColorGradientStopWidget * widget);
    
protected:
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    void paintEvent(QPaintEvent * event) override;
    
protected:
    void updatePosition();
    
private:
    QColor m_color;
    qreal m_position;
    
    QPoint m_mousePos;
    QPoint m_initialPos;
    bool m_pressed;
};

} // namespace widgetzeug