#include <propertyguizeug/PropertyEditor.h>

#include <QHBoxLayout>

namespace propertyguizeug
{
	
PropertyEditor::PropertyEditor(QWidget * parent)
:	QWidget(parent)
,	m_layout(new QHBoxLayout(this))
{
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
}

QBoxLayout * PropertyEditor::boxLayout()
{
	return m_layout;
}

} // namespace propertyguizeug
