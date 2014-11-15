#pragma once

#include <QWidget>

#include <propertyguizeug/propertyguizeug_api.h>

class QHBoxLayout;

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API PropertyEditor : public QWidget
{
public:
	PropertyEditor(QWidget * parent = nullptr);

protected:
    void addWidget(QWidget * widget);
	QHBoxLayout * boxLayout();
	
private:
	QHBoxLayout * m_layout;
};

} // namespace propertyguizeug
