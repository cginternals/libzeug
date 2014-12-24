#pragma once

#include <QList>
#include <QWidget>

namespace widgetzeug
{

class ColorGradientStop;
class ColorGradientStopWidget;

class ColorGradientStopBar : public QWidget
{
    Q_OBJECT

public:
    ColorGradientStopBar(
        const QList<ColorGradientStop> & stops,
        QWidget * parent = nullptr);
    
    void newStop(
        const QColor & color,
        qreal position);
    
    QList<ColorGradientStop> stops() const;
    
signals:
    void onResized(const QSize & size);
    void onStopsChanged();
    
protected:
    void resizeEvent(QResizeEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    
protected:
    void stopPositionChanged(ColorGradientStopWidget * stopWidget);
    void stopColorChanged(ColorGradientStopWidget * stopWidget);
    
private:
    void addStop(ColorGradientStopWidget * stopWidget);

private:
    QList<ColorGradientStopWidget *> m_stops;
};

} // namespace widgetzeug