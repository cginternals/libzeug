
#include <widgetzeug/DockableScrollAreaWidget.h>

#include <QScrollArea>
#include <QVBoxLayout>
#include <QGroupBox>


namespace widgetzeug
{

DockableScrollAreaWidget::DockableScrollAreaWidget(const QString & title, QWidget * parent, Qt::WindowFlags flags)
: QDockWidget(title, parent, flags)
, m_scrollArea{ new QScrollArea }
, m_vbox{ new QVBoxLayout }
{
    layout()->setContentsMargins(0, 0, 0, 0);

    m_vbox->addStretch();
    
    auto widget = new QWidget();
    widget->setLayout(m_vbox);  // this extra widget is required in order to make the scroll area work as expected

    m_scrollArea->setWidget(widget);
    m_scrollArea->setWidgetResizable(true);

    m_scrollArea->setFrameShape(QFrame::NoFrame);

    setWidget(m_scrollArea);
}

DockableScrollAreaWidget::DockableScrollAreaWidget(QWidget * parent, Qt::WindowFlags flags)
: DockableScrollAreaWidget("", parent, flags)
{
}

void DockableScrollAreaWidget::addWidget(QWidget * widget, int stretch)
{
    if (!widget)
        return;

    auto group = new QGroupBox(widget->windowTitle(), m_scrollArea);

    group->setFlat(true);
    group->setLayout(new QVBoxLayout());

    group->layout()->addWidget(widget);
    group->layout()->setContentsMargins(0, 0, 0, 0);

    m_vbox->insertWidget(m_vbox->count() - 1, group, stretch);
}

} // namespace widgetzeug
