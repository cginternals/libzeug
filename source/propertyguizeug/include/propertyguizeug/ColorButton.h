
#pragma once

#include <QLabel>
#include <QColor>

#include <propertyguizeug/propertyguizeug_api.h>


namespace propertyguizeug
{

class PROPERTYGUIZEUG_API ColorButton : public QLabel
{
	Q_OBJECT

public:
	ColorButton(const QColor & initialColor = Qt::black, QWidget * parent = nullptr);
	virtual ~ColorButton();

	virtual const QColor & color() const;
	void setColor(const QColor & color);

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
