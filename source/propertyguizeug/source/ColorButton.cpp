#include <propertyguizeug/ColorButton.h>

#include <QColorDialog>
#include <QGridLayout>
#include <QPainter>
#include <QStyle>

#include "TransparencyBackgroundBrush.hpp"

namespace propertyguizeug
{

QSize ColorButton::sizeFromFontHeight(int height)
{
    static const auto factor = 1.1875f;
    const auto extent = static_cast<int>(height * factor);
    return {extent, extent};
}

void ColorButton::paint(
    QPainter * painter,
    const QPoint & topLeft, 
    const QColor & color)
{
    const auto metrics = painter->fontMetrics();
    const auto size = sizeFromFontHeight(metrics.height());
    const auto rect = QRect{topLeft, size};

    auto pixmap = QPixmap{size};
    pixmap.fill(color);

    painter->save();
    painter->setBrushOrigin(topLeft);
    painter->fillRect(rect, TransparencyBackgroundBrush());
    painter->drawPixmap(rect, pixmap);
    painter->restore();
}

ColorButton::ColorButton(QWidget * parent, const QColor & initialColor)
:   QLabel{parent}
{
    const auto metrics = fontMetrics();

    auto palette = QPalette{};
    palette.setBrush(QPalette::Background, QBrush(TransparencyBackgroundBrush()));

    setFrameStyle(QFrame::NoFrame);
	setAutoFillBackground(true);
    setFixedSize(sizeFromFontHeight(metrics.height()));
	setBackgroundRole(QPalette::Background);
	setPalette(palette);
	setColor(initialColor);
}

const QColor & ColorButton::color() const
{
	return m_color;
}

void ColorButton::setColor(const QColor & color)
{
	m_color = color;
	updateColor();
}

void ColorButton::mousePressEvent(QMouseEvent * event)
{
    emit pressed();
}

void ColorButton::updateColor() 
{
    const auto metrics = fontMetrics();
    auto pixmap = QPixmap{sizeFromFontHeight(metrics.height())};
    pixmap.fill(m_color);
	setPixmap(pixmap);
}

} // namespace propertyguizeug
