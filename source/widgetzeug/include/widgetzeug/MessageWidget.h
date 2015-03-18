#pragma once

#include <QHash>
#include <QTextBrowser>

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/AbstractMessageReceiver.h>

class QUrl;


namespace widgetzeug
{

/** \brief ToDo
*
*
* \code{.cpp}
* Moep
* \endcode
*/
class WIDGETZEUG_API MessageWidget : public QTextBrowser, public AbstractMessageReceiver
{
public:
    MessageWidget(QWidget * parent = 0);
    virtual ~MessageWidget();

    virtual void print(
        QtMsgType type
    ,   const QMessageLogContext & context
    ,   const QDateTime & timestamp
    ,   const QString & message);

    void setDetectLinks(bool enable);
    bool detectLinks() const;

    void setDetectControlCharacters(bool enable);
    bool detectControlCharacters() const;

protected slots:
    void onAnchorClicked(const QUrl & link);

protected:
    QHash<QtMsgType, QString> m_colors;
    bool m_detectLinks;
    bool m_detectControlCharacters;
};

} // namespace widgetzeug
