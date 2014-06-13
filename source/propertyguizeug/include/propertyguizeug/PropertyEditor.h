
#pragma once

#include <QWidget>

#include <propertyguizeug/propertyguizeug_api.h>

class QBoxLayout;

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API PropertyEditor : public QWidget
{
public:
	PropertyEditor(QWidget * parent = nullptr);
	virtual ~PropertyEditor();

protected:
	QBoxLayout * boxLayout();
	
private:
	QBoxLayout * m_layout;

};

} // namespace propertyguizeug
