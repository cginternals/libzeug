
#include <QChildEvent>
#include <QKeyEvent>
#include <QApplication>
#include <QHBoxLayout>

#include "PropertyEditor.h"

namespace zeug 
{
	
PropertyEditor::PropertyEditor(QWidget * parent)
:	QWidget(parent)
,	m_layout(new QHBoxLayout(this))
{
    m_layout->setContentsMargins(s_horizontalMargin, 0, s_horizontalMargin, 0);
    m_layout->setSpacing(s_spacing);
}

PropertyEditor::~PropertyEditor()
{
}

void PropertyEditor::childEvent(QChildEvent * event)
{
    event->child()->installEventFilter(this);
}

bool PropertyEditor::eventFilter(QObject * object, QEvent * event)
{
    if (event->type() != QEvent::KeyPress)
        return false;

    QKeyEvent * keyEvent = static_cast<QKeyEvent *>(event);

    if (!(keyEvent->key() == Qt::Key_Tab || keyEvent->key() == Qt::Key_Backtab))
        return false;

    QApplication::sendEvent(this, event);
    return true;
}

QBoxLayout * PropertyEditor::boxLayout() const
{
	return m_layout;
}

} // namespace zeug