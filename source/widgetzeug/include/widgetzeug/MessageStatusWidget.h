#pragma once

#include <QWidget>
#include <QMap>
#include <QStyle>

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/AbstractMessageReceiver.h>

class QLabel;

namespace widgetzeug
{

/** \brief Widget that displays QtMsgType appropriate Status Icons.
*
* If attached to a MessageHandler, this widget will cound received messages
* and display (currently three) type specifc status icons with tool tips, 
* hinting the number of received messages (of that specific type).
*
* \see MessageHandler
*/
class WIDGETZEUG_API MessageStatusWidget : public QWidget, public AbstractMessageReceiver
{
public:
    MessageStatusWidget(
        QWidget * parent = nullptr
    ,   Qt::WindowFlags flags = 0);

    virtual ~MessageStatusWidget();

    virtual void print(
        QtMsgType type
    ,   const QMessageLogContext & context
    ,   const QDateTime & timestamp
    ,   const QString & message);

    /**
    * Allows to link a single widget to the status widget, that will be shown 
    * on single left clicking the status widget.
    */
    void attachWidget(QWidget * widget);
    QWidget * widget();

protected:
    /**
    * Creates a message type appropriate icon label and updates its state.
    */
    void setupLabel(QtMsgType type, QStyle::StandardPixmap pixmap);
    /**
    * Checks the message type related message count and updates the 
    * related icons tool tip and enabled status.
    */
    void updateStatus(QtMsgType type);

protected:
    /**
    * Depending on the button, either shows the attached widget, if exists and 
    * hidden (lmb), or resets the message count for each message type and 
    * updates its status (rmb).
    */
    virtual void mouseReleaseEvent(QMouseEvent * event);

protected:
    QWidget * m_widget;

    QMap<QtMsgType, QLabel*> m_iconByMessageType;
    QMap<QtMsgType, int> m_countByMessageType;
};

} // namespace widgetzeug
