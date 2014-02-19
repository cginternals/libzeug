
#include <QColorDialog>
#include <QGridLayout>
#include <QPainter>

#include "TransparencyBackgroundBrush.hpp"
#include "ColorButton.h"

namespace propertyguizeug
{

const QSize ColorButton::s_fixedSize = QSize(19, 19);

ColorButton::ColorButton(const QColor & initialColor, QWidget * parent)
:	QLabel(parent)
{
    this->setFrameStyle(QFrame::NoFrame);
	this->setAutoFillBackground(true);
    
    this->setFixedSize(s_fixedSize);

	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(TransparencyBackgroundBrush()));
	setBackgroundRole(QPalette::Background);
	setPalette(palette);

	this->setColor(initialColor);
}


ColorButton::~ColorButton()
{
}


const QColor ColorButton::color() {
	return m_color;
}

void ColorButton::setColor(const QColor & color)
{
	m_color = color;
	updateColor();
}

void ColorButton::paint(QPainter * painter, const QPoint & topLeft, const QColor & color)
{
    QPixmap pixmap(s_fixedSize);
    pixmap.fill(color);

    QRect rect(topLeft, s_fixedSize);

    painter->setBrushOrigin(topLeft);
    painter->fillRect(rect, TransparencyBackgroundBrush());
    painter->drawPixmap(rect, pixmap);
}

void ColorButton::mousePressEvent(QMouseEvent * event)
{
    emit this->pressed();
}

void ColorButton::updateColor() 
{
	QPixmap pixmap(s_fixedSize);
    pixmap.fill(m_color);
	setPixmap(pixmap);
}

} // namespace propertyguizeug
