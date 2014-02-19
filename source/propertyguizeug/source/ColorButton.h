
#pragma once

#include <QLabel>
#include <QColor>

namespace propertyguizeug
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

public:
    static void paint(QPainter * painter, const QPoint & topLeft, const QColor & color);
    static const QSize s_fixedSize;

protected:
	virtual void mousePressEvent(QMouseEvent * event);
    void updateColor();
    
    QColor m_color;

};

} // namespace propertyguizeug
