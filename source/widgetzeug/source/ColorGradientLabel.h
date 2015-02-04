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
    
    ~ColorGradientLabel();
    
    void setModel(ColorGradientModel * model);
    void setHistogram(const QList<uint> & histogram);

protected:
    void resizeEvent(QResizeEvent * event) override;
    void paintEvent(QPaintEvent * event) override;
    
private:
    static const uint s_bucketSize = 6u;
    
    QList<qreal> generateBuckets(uint numBuckets);
    void updateHistogram();
    void updatePixmap();
    
    void paintGradient(const QRect & paintRect, QPainter & painter);
    void paintHistogram(QPainter & painter);

private:
    ColorGradientModel * m_model;
    QList<uint> m_histogram;
    
    QPixmap m_gradientPixmap;
    QBrush m_backgroundBrush;
    QPainterPath m_histogramPath;
    
    QMetaObject::Connection m_modelConnection;
};

} // namespace widgetzeug