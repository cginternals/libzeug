#pragma once

#include <QList>
#include <QWidget>

namespace widgetzeug
{

class ColorGradientModel;
class ColorGradientStopWidget;

class ColorGradientStopBar : public QWidget
{
    Q_OBJECT

public:
    ColorGradientStopBar(
        ColorGradientModel * model,
        QWidget * parent = nullptr);
    
    void newStop(
        const QColor & color,
        qreal position);
    
signals:
    void resized(const QSize & size);
    
protected:
    void resizeEvent(QResizeEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    
protected:
    void onStopPositionChanged(ColorGradientStopWidget * stopWidget);
    
private:
    void addStop(ColorGradientStopWidget * stopWidget);

private:
    ColorGradientModel * m_model;
    QList<ColorGradientStopWidget *> m_stopWidgets;
};

} // namespace widgetzeug