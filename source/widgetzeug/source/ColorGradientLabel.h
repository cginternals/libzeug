#pragma once

#include <QPixmap>
#include <QGLWidget>

namespace widgetzeug
{

class ColorGradientModel;

class ColorGradientLabel : public QGLWidget
{
public:
    ColorGradientLabel(QWidget * parent);

    ColorGradientLabel(
        ColorGradientModel * model,
        QWidget * parent);
    
    void setModel(ColorGradientModel * model);

protected:
    void resizeEvent(QResizeEvent * event) override;
    void paintEvent(QPaintEvent * event) override;
    
private:
    static const uint s_bucketSize = 6u;

    void updatePixmap();
    QList<qreal> generateBuckets(uint numBuckets);

private:
    ColorGradientModel * m_model;
    QPixmap m_pixmap;
    QBrush m_backgroundBrush;
    
    // WIP
    QPainterPath m_path;
    QList<qreal> m_buckets;
};

} // namespace widgetzeug