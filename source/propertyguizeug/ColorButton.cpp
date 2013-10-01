
#include <propertyguizeug/ColorButton.h>

#include <QColorDialog>
#include <QGridLayout>

#include <propertyguizeug/TransparencyBackgroundBrush.hpp>

ColorButton::ColorButton(const QColor & initialColor, QWidget * parent)
:	QLabel(parent)
{
	this->setFrameShape(QFrame::StyledPanel);
	this->setFrameShadow(QFrame::Raised);
	
	this->setAutoFillBackground(true);

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
	QPixmap pixmap(20, 20);
    pixmap.fill(m_color);
	setPixmap(pixmap);
}

