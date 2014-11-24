#pragma once

#include <QColor>
#include <QLabel>

#include <propertyguizeug/propertyguizeug_api.h>

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API ColorButton : public QLabel
{
	Q_OBJECT

public:
    static QSize sizeFromFontHeight(int height, bool forWidget);

    static void paint(
        QPainter * painter,
        QStyle * style, 
        const QPoint & topLeft, 
        const QColor & color);
    
public:
	ColorButton(QWidget * parent = nullptr, const QColor & initialColor = Qt::black);

	virtual const QColor & color() const;
	void setColor(const QColor & color);

signals:
    void pressed();

protected:
	virtual void mousePressEvent(QMouseEvent * event);
    void updateColor();
    
private:
    QColor m_color;
};

} // namespace propertyguizeug
