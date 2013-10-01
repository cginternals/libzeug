
#pragma once

#include <QLabel>
#include <QColor>
#include "propertyguizeug.h"

class PROPERTYGUIZEUG_API ColorButton : public QLabel
{
	Q_OBJECT

public:
	ColorButton(const QColor & initialColor = Qt::black, QWidget* parent = nullptr);
	virtual ~ColorButton();

	virtual const QColor color();

public slots:
	void setColor(const QColor &color);
    
signals:
	void pressed();

protected:
	virtual void mousePressEvent(QMouseEvent *event);
    void updateColor();
    
    QColor m_color;

};
