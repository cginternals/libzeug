

#include <QColorDialog>
#include <QGridLayout>

#include "TransparencyBackgroundBrush.hpp"
#include "ColorButton.h"

namespace zeug
{

const QSize ColorButton::s_fixedSize = QSize(20, 20);

ColorButton::ColorButton(const QColor & initialColor, QWidget * parent)
:	QLabel(parent)
{
    this->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
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

} // namespace zeug
