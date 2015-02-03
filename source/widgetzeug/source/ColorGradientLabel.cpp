#include "ColorGradientLabel.h"

#include <cassert>

#include <algorithm>
#include <limits>

#include <QDebug>

#include <QPainter>
#include <QPaintEvent>

#include "ColorGradientModel.h"

namespace
{

const QBrush TransparencyBackgroundBrush()
{
    const int size = 12;
    QImage backgroundImage(size, size, QImage::Format_ARGB32);
    unsigned char *bits = backgroundImage.bits();
    
    int color, i;
    for(unsigned short x = 0; x < size; ++x)
        for(unsigned short y = 0; y < size; ++y)
        {
            i = (x * size + y) * 4;
            
            color = (x <= 5 && y <= 5) || (x > 5 && y > 5) ? 255 : 224;
            
            bits[i + 2] = color;
            bits[i + 1] = color;
            bits[i + 0] = color;
            bits[i + 3] = 255;
        }
    
    return QBrush(backgroundImage);
};

QList<uint> generateHistogramm()
{
    return { 21,14,10,22,42,58,130,227,377,540,816,1424,1674,2172,2453,2533,2515,2285,2337,2761,2896,2702,2495,2508,2641,2686,2845,2982,2984,3171,3301,3335,3380,3436,3378,3396,3544,3622,3695,3745,3842,3751,3710,3763,3779,3702,3840,3920,3807,3663,3724,3663,3537,3450,3506,3335,3158,3165,3137,3073,3120,3005,3009,3060,3017,3029,2908,2980,2848,2789,2819,2788,2783,2803,2738,2813,2647,2715,2704,2735,2660,2752,2882,2796,2977,2751,2786,2730,2582,2827,2728,2795,2722,2634,2440,2544,2408,2500,2510,2552,2474,2470,2454,2617,2738,2867,3045,3163,3351,3169,3343,3361,3701,4008,4296,4027,3864,3703,3681,3763,3770,3828,3988,3757,3769,3897,3824,3668,3666,3718,3894,3808,4109,3987,3946,3889,4007,3923,3711,3672,3642,3645,3476,3319,3463,3388,3284,3453,3478,3694,4008,3963,4079,3932,3833,3756,3462,3061,2692,2579,2345,2172,1874,1754,1844,1897,1982,1899,1903,2018,2067,2099,1961,2069,2222,2219,2152,2061,1931,1927,1879,1787,1850,1822,1857,1913,1863,2015,2035,2026,1896,1905,1940,1951,1850,1756,1792,1715,1699,1621,1613,1644,1577,1608,1682,1851,1808,1690,1526,1432,1354,1271,1103,1031,957,815,783,633,614,503,445,350,320,281,278,244,252,196,184,181,179,152,150,142,130,127,114,123,121,102,96,103,109,94,88,110,81,103,91,97,62,80,82,69,131,597};
}

} // namespace

namespace widgetzeug
{

ColorGradientLabel::ColorGradientLabel(QWidget * parent)
:   QGLWidget{parent}
,   m_model{nullptr}
,   m_backgroundBrush{TransparencyBackgroundBrush()}
{
    setMinimumSize(1u, 30);
}

ColorGradientLabel::ColorGradientLabel(
    ColorGradientModel * model,
    QWidget * parent)
:   ColorGradientLabel{parent}
{
    setModel(model);
}

void ColorGradientLabel::setModel(widgetzeug::ColorGradientModel * model)
{
    if (m_model)
        m_model->disconnect(this);
    
    m_model = model;
    updatePixmap();
    
    connect(model, &ColorGradientModel::changed,
            this, &ColorGradientLabel::updatePixmap);
}

void ColorGradientLabel::resizeEvent(QResizeEvent * event)
{
    if (!m_model)
        return;
    
    m_buckets = generateBuckets(event->size().width() / s_bucketSize);
    
    updatePixmap();
}

void ColorGradientLabel::paintEvent(QPaintEvent * event)
{
    QPainter painter{this};
    
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_backgroundBrush);
    painter.drawRect(event->rect());
    
    painter.drawPixmap(event->rect(), m_pixmap);
    
    painter.setPen(QColor{0, 0, 0, 100});
    painter.setBrush(QColor{255, 255, 255, 70});
    
    static const auto offset = 2u;
    const auto width = event->rect().width();
    const auto height = event->rect().height();
    const auto paddingTop = static_cast<uint>(height * 0.2);
    const auto maxRange = static_cast<uint>(height * 0.7);
    
    const auto initialX = (width % s_bucketSize) / 2;
    auto currentX = initialX;
    
    auto path = QPainterPath{};
    path.moveTo(currentX, height + offset);
    
    for (const auto & value : m_buckets)
    {
        const auto y = paddingTop + (1.0 - value) * maxRange;
        
        path.lineTo(currentX, y);
        currentX += s_bucketSize;
        path.lineTo(currentX, y);
    }
    
    path.lineTo(currentX, height + offset);
    path.lineTo(initialX, height + offset);

    painter.drawPath(path);
}

void ColorGradientLabel::updatePixmap()
{
    auto image = m_model->image(width() * devicePixelRatio());
    m_pixmap = QPixmap::fromImage(image);
    m_pixmap.setDevicePixelRatio(devicePixelRatio());
    
    repaint();
}

QList<qreal> ColorGradientLabel::generateBuckets(uint numBuckets)
{
    auto histogramm = generateHistogramm();
    
    auto buckets = QList<qreal>{};
    
    const auto invNumBuckets = 1.0 / numBuckets;
    
    auto histogramm_index = 0;
    for (auto bucket_i = 0; bucket_i < numBuckets; ++bucket_i)
    {
        const auto norm_bucket_i = static_cast<qreal>(bucket_i) / numBuckets;
        auto count = 0u;
        
        while (static_cast<qreal>(histogramm_index) / histogramm.size() < (norm_bucket_i + invNumBuckets))
            count += histogramm[histogramm_index++];
        
        buckets << count;
    }
    
    assert(histogramm_index == histogramm.size());
    
    auto min = std::numeric_limits<qreal>::max(), max = 0.0;
    for (const auto & value : buckets)
    {
        min = std::min(min, value);
        max = std::max(max, value);
    }
    
    const auto diff = (max - min);
    
    for (auto & value : buckets)
    {
        value = static_cast<qreal>(value - min) / diff;
        assert(value >= 0.0 && value <= 1.0);
    }
    
    return buckets;
}

} // namespace widgetzeug