#include "ColorGradientLabel.h"

#include <cassert>

#include <algorithm>
#include <limits>

#include <QDebug>

#include <QPainter>
#include <QPaintEvent>

#include "ColorGradientModel.h"

#include "util.hpp"

namespace
{

const QBrush TransparencyBackgroundBrush()
{
    static const auto size = 12;
    
    QImage backgroundImage(size, size, QImage::Format_ARGB32);
    auto bits = backgroundImage.bits();

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

ColorGradientLabel::~ColorGradientLabel()
{
    if (m_model)
        m_model->disconnect(m_modelConnection);
}

void ColorGradientLabel::setModel(widgetzeug::ColorGradientModel * model)
{
    if (m_model)
        m_model->disconnect(m_modelConnection);
    
    m_model = model;
    updatePixmap();
    update();
    
    m_modelConnection = connect(model, &ColorGradientModel::changed,
        [this] ()
        {
            updatePixmap();
            update();
        });
}

void ColorGradientLabel::setHistogram(const QList<uint> & histogram)
{
    m_histogram = histogram;

    updateHistogram();
    update();
}

void ColorGradientLabel::resizeEvent(QResizeEvent * event)
{
    if (!m_model)
        return;
    
    updateHistogram();
    updatePixmap();
    
    update();
}

void ColorGradientLabel::paintEvent(QPaintEvent * event)
{
    QPainter painter{this};
    
    paintGradient(event->rect(), painter);
    paintHistogram(painter);
}

void ColorGradientLabel::paintGradient(const QRect & paintRect, QPainter & painter)
{
    painter.save();

    painter.setPen(Qt::NoPen);
    painter.setBrush(m_backgroundBrush);
    painter.drawRect(paintRect);
    
    painter.drawPixmap(paintRect, m_gradientPixmap);

    painter.restore();
}

void ColorGradientLabel::paintHistogram(QPainter & painter)
{
    if (m_histogram.empty())
        return;

    const auto width = this->width();
    const auto widthScale = width / static_cast<qreal>(m_numBuckets * m_actualBucketSize);

    painter.save();

    auto pen = QPen{QColor{0, 0, 0, 100}};
    pen.setWidthF(1.0 / devicePixelRatio());
    painter.setPen(pen);
    painter.setBrush(QColor{255, 255, 255, 70});

    painter.scale(widthScale, 1.0);
    painter.drawPath(m_histogramPath);

    painter.restore();
}

QList<qreal> ColorGradientLabel::generateBuckets(uint numBuckets)
{
    auto buckets = QList<qreal>{};
    
    if (numBuckets < static_cast<unsigned int>(m_histogram.size()))
    {
        const auto invNumBuckets = 1.0 / numBuckets;
        
        auto histogram_index = 0;
        for (auto bucket_i = 0u; bucket_i < numBuckets; ++bucket_i)
        {
            const auto norm_bucket_i = static_cast<qreal>(bucket_i) / numBuckets;
            auto value = 0u, count = 0u;
            
            while (static_cast<qreal>(histogram_index) / m_histogram.size() < (norm_bucket_i + invNumBuckets))
            {
                count += 1;
                value += m_histogram[histogram_index++];
            }
            
            buckets << value / count;
        }
        
        assert(histogram_index == m_histogram.size());
    }
    else
    {
        std::copy(
            m_histogram.begin(),
            m_histogram.end(),
            std::back_inserter(buckets));
    }
    
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
    
    for (auto i = 0; i < buckets.size(); ++i)
    {
        const auto prev = std::max(0, i - 1);
        const auto next = std::min(buckets.size() - 1, i + 1);
        
        buckets[i] = (buckets[prev] + buckets[i] + buckets[next]) / 3.0;
    }
    
    return buckets;
}

void ColorGradientLabel::updateHistogram()
{
    if (m_histogram.empty())
    {
        m_histogramPath = QPainterPath{};
        return;
    }

    const auto buckets = generateBuckets(width() / s_bucketSize);
    
    m_numBuckets = buckets.size();
    m_actualBucketSize = width() / m_numBuckets;
    
    static const auto offset = 2u;
    
    const auto height = this->height();
    const auto paddingTop = static_cast<uint>(height * 0.2);
    const auto maxRange = static_cast<uint>(height * 0.7);
    
    const auto initialX = 0.0;
    auto currentX = initialX;
    
    m_histogramPath = QPainterPath{};
    m_histogramPath.moveTo(currentX, height + offset);
    
    for (const auto & value : buckets)
    {
        const auto y = paddingTop + (1.0 - value) * maxRange;
        
        m_histogramPath.lineTo(currentX, y);
        currentX += m_actualBucketSize;
        m_histogramPath.lineTo(currentX, y);
    }
    
    m_histogramPath.lineTo(currentX, height + offset);
    m_histogramPath.lineTo(initialX, height + offset);
}

void ColorGradientLabel::updatePixmap()
{
    auto image = m_model->image(width() * devicePixelRatio());
    m_gradientPixmap = QPixmap::fromImage(image);
    m_gradientPixmap.setDevicePixelRatio(devicePixelRatio());
}

} // namespace widgetzeug
