
#pragma once

#include <QBrush>
#include <QImage>

inline const QBrush TransparencyBackgroundBrush()
{
    const int size = 13;
	QImage backgroundImage(size, size, QImage::Format_ARGB32);
	unsigned char *bits = backgroundImage.bits();

	int color, i;
	for(unsigned short x = 0; x < size; ++x)
		for(unsigned short y = 0; y < size; ++y) {		
			i = (x * size + y) * 4;
            
			color = (x <= 5 && y <= 5) || (x > 5 && y > 5) ? 255 : 224;

			bits[i + 2] = color;
			bits[i + 1] = color;
			bits[i + 0] = color;
			bits[i + 3] = 255;
		}

	return QBrush(backgroundImage);
};