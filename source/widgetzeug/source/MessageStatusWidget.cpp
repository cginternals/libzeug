
#include <widgetzeug/MessageStatusWidget.h>

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPixmap>
#include <QTimer>

#include <widgetzeug/MessageWidget.h>


namespace widgetzeug
{

MessageStatusWidget::MessageStatusWidget(QWidget * parent, Qt::WindowFlags flags)
: QWidget(parent, flags)
, m_widget(nullptr)
{
    setLayout(new QHBoxLayout());
    layout()->setContentsMargins(0, 0, 0, 0);

    setupLabel(QtMsgType::QtDebugMsg, QStyle::SP_MessageBoxInformation);
    setupLabel(QtMsgType::QtWarningMsg, QStyle::SP_MessageBoxWarning);
    setupLabel(QtMsgType::QtCriticalMsg, QStyle::SP_MessageBoxCritical);

    // QtMsgType::QtFatalMsg is not required, since it should trigger an assertion 
    // or result in application exit (and there is no appropriate default icon :).   
}

MessageStatusWidget::~MessageStatusWidget()
{
}

void MessageStatusWidget::setupLabel(const QtMsgType type, const QStyle::StandardPixmap pixmap)
{
    m_iconByMessageType[type] = new QLabel;
    m_iconByMessageType[type]->setPixmap(style()->standardIcon(pixmap).pixmap(QSize(12, 12)));

    layout()->addWidget(m_iconByMessageType[type]);

    m_countByMessageType[type] = 0;
    updateStatus(type);
}

void MessageStatusWidget::updateStatus(const QtMsgType type)
{
    if (!m_iconByMessageType.contains(type))
        return;

    const int count = m_countByMessageType[type];
    QString toolTip = QString("%1 ").arg(count);

    switch (type)
    {
    case QtMsgType::QtDebugMsg:
        toolTip.append(tr("Debug Message"));
        break;
    case QtMsgType::QtWarningMsg:
        toolTip.append(tr("Warning"));
        break;
    case QtMsgType::QtCriticalMsg:
        toolTip.append(tr("Critical Message"));
        break;
    default:
        break;
    }
    if (count != 1)
        toolTip.append(tr("s", "plural suffix"));

    m_iconByMessageType[type]->setEnabled(count > 0);
    m_iconByMessageType[type]->setToolTip(toolTip);
}

void MessageStatusWidget::attachWidget(QWidget * widget)
{
    m_widget = widget;
}

QWidget * MessageStatusWidget::widget()
{
    return m_widget;
}

void MessageStatusWidget::print(
    const QtMsgType type
,   const QMessageLogContext &
,   const QDateTime &
,   const QString &)
{
    if (!m_countByMessageType.contains(type))
        return;

    ++m_countByMessageType[type];
    updateStatus(type);
}

void MessageStatusWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton
     && m_widget && m_widget->isHidden())
    {
        m_widget->show();
        event->accept();
    }
    else if (event->button() == Qt::MouseButton::RightButton)
    {
        m_countByMessageType[QtMsgType::QtDebugMsg] = 0;
        updateStatus(QtDebugMsg);
        m_countByMessageType[QtMsgType::QtWarningMsg] = 0;
        updateStatus(QtWarningMsg);
        m_countByMessageType[QtMsgType::QtCriticalMsg] = 0;
        updateStatus(QtCriticalMsg);

        event->accept();
    }
    QWidget::mousePressEvent(event);
}

} // namespace widgetzeug
