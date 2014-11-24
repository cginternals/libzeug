#pragma once

#include <QWidget>

#include <propertyguizeug/propertyguizeug_api.h>

class QHBoxLayout;
class QPainter;
class QStyleOptionViewItem;

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API PropertyEditor : public QWidget
{
public:
    static void drawString(const QString & string, 
                           QPainter * painter, 
                           const QStyleOptionViewItem & option);

public:
	PropertyEditor(QWidget * parent = nullptr);

protected:
    void addWidget(QWidget * widget);
	QHBoxLayout * boxLayout();
	
private:
	QHBoxLayout * m_layout;
};

} // namespace propertyguizeug
