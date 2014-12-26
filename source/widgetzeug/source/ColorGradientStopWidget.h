#pragma once

#include <QColor>
#include <QWidget>

namespace widgetzeug
{

class ColorGradientStopBar;
class ColorGradientStopModel;

class ColorGradientStopWidget : public QWidget
{
    Q_OBJECT

public:
    ColorGradientStopWidget(
        ColorGradientStopModel * model,
        ColorGradientStopBar * bar);
    
    ColorGradientStopModel * model() const;
    
signals:
    void positionChanged(ColorGradientStopWidget * widget);
    
protected:
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    void paintEvent(QPaintEvent * event) override;
    
protected:
    void updatePosition();
    
private:
    ColorGradientStopModel * m_model;
    
    QPoint m_mousePos;
    QPoint m_initialPos;
    bool m_pressed;
};

} // namespace widgetzeug