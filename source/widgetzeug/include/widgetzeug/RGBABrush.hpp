#pragma once

#include <QBrush>
#include <QImage>

namespace widgetzeug
{

inline const QBrush RGBABrush(
    const QColor & color = QColor::fromRgbF(0.f, 0.f, 0.f, 0.f)
,   const QSize & halfSize = QSize(8, 8))
{
    const QSize size = halfSize * 2;
    QImage image(size, QImage::Format_ARGB32);
    unsigned char *bits = image.bits();

    float bg;
    int  i;

    const float r = color.redF();
    const float g = color.greenF();
    const float b = color.blueF();
    const float a = color.alphaF();

    for (unsigned short y = 0; y < size.height(); ++y)
	    for(unsigned short x = 0; x < size.width(); ++x)
        {
			i = (y * size.width() + x) * 4;
            bg = (x < halfSize.width() && y < halfSize.width()) || (x > halfSize.width() - 1 && y > halfSize.width() - 1) ? 1.f : 224.f / 255.f;

			bits[i + 2] = static_cast<unsigned char>(255 * ((1 - a) * bg + a * r));
            bits[i + 1] = static_cast<unsigned char>(255 * ((1 - a) * bg + a * g));
            bits[i + 0] = static_cast<unsigned char>(255 * ((1 - a) * bg + a * b));
			bits[i + 3] = 255;
		}

    return QBrush(image);
};

} // namespace widgetzeug
