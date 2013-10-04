
#pragma once

#include <QLabel>
#include <QColor>

namespace zeug
{

class ColorButton : public QLabel
{
	Q_OBJECT

public:
	ColorButton(const QColor & initialColor = Qt::black, QWidget* parent = nullptr);
	virtual ~ColorButton();

	virtual const QColor color();
	void setColor(const QColor &color);
    
signals:
	void pressed();

protected:
    static const QSize s_fixedSize;

	virtual void mousePressEvent(QMouseEvent *event);
    void updateColor();
    
    QColor m_color;

};

} // namespace zeug