
#pragma once

#include <QBrush>
#include <QImage>

inline const QBrush TransparencyBackgroundBrush()
{
	QImage backgroundImage(16, 16, QImage::Format_ARGB32);
	unsigned char *bits = backgroundImage.bits();

	int color, i;
	for(unsigned short x = 0; x < 16; ++x)
		for(unsigned short y = 0; y < 16; ++y) {		
			i = x * 16 * 4 + y * 4;
			color = (x < 8 && y < 8) || (x > 7 && y > 7) ? 255 : 224;

			bits[i + 2] = color;
			bits[i + 1] = color;
			bits[i + 0] = color;
			bits[i + 3] = 255;
		}

	return QBrush(backgroundImage);
};