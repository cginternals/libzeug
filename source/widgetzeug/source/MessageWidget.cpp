
#include <widgetzeug/MessageWidget.h>

#include <cassert>

#include <QDateTime>
#include <QDesktopServices>
#include <QString>
#include <QFont>
#include <QFileInfo>
#include <QUrl>


namespace widgetzeug
{

MessageWidget::MessageWidget(QWidget * parent)
:	QTextBrowser(parent)
, m_detectLinks(true)
{
    setTextInteractionFlags(Qt::TextBrowserInteraction | Qt::TextSelectableByKeyboard);

    // since the textbrowser opens local files directly, open links is overriden in anchorClicked... 
	setOpenLinks(false);
    connect(this, &QTextBrowser::anchorClicked, this, &MessageWidget::onAnchorClicked);

    setFont(QFont("Consolas, Courier New"));

    m_colors[QtMsgType::QtDebugMsg]    = "#2b91af";
    m_colors[QtMsgType::QtWarningMsg]  = "#2f4f4f";
    m_colors[QtMsgType::QtCriticalMsg] = "#a31515";
    m_colors[QtMsgType::QtFatalMsg]    = "#a31515";
}

MessageWidget::~MessageWidget()
{
}

void MessageWidget::print(
    const QtMsgType type
,   const QMessageLogContext & context
,   const QDateTime & timestamp
,   const QString & message)
{
#ifdef _NDEBUG
	const QString t(timestamp.toString("hh:mm:ss"));
#else
	const QString t(timestamp.toString("hh:mm:ss:zzz"));
#endif
	//const QString timestamp(entry.timestamp().toString("hh:mm:ss"));

    QString html;
	switch (type)
	{
    case QtMsgType::QtDebugMsg:
#ifdef _DEBUG
        html = QString("%1 %2(%3): %4\n").arg(t).arg(context.file).arg(context.line).arg(message);
#else
		html = QString("%1: %2\n").arg(t).arg(message);
#endif
		break;

    case QtMsgType::QtCriticalMsg:
    case QtMsgType::QtFatalMsg:
    case QtMsgType::QtWarningMsg:
		html = QString("%1: %2\n").arg(t).arg(message);
		break;

    default:
		break;
	};

    if (m_detectLinks)
    {
        QRegExp reHttp("\\b(?:(?:https?|ftp):\\/\\/(\\/)?|www\\.|ftp\\.)[-\\w\\+&@#\\/%=~|\\$?!:,\\.]*[\\w\\+&@#/%=~_\\$]", Qt::CaseInsensitive);
        QRegExp reFile("\\b(?:(?:file):\\/\\/(\\/)?){1,1}[-\\w\\+&@#\\/%=~|\\$?!:,\\.]*[\\w\\+&@#\\/%=~_\\$]", Qt::CaseInsensitive);
        QRegExp reMail("\\b(?:((?:mailto:)?[\\w\\._%+-]+@[\\w\\._%-]+\\.[A-Z]{2,})\\b)", Qt::CaseInsensitive);

        assert(reHttp.isValid());
        assert(reFile.isValid());
        assert(reMail.isValid());

        int pos = 0;
        while ((pos = reHttp.indexIn(message, pos)) != -1)
        {
            pos += reHttp.matchedLength();
            const QString uri = reHttp.capturedTexts()[0];
            html.replace(uri, QString("<a href =\"%1\">%1</a>").arg(uri));
        }

        pos = 0;
        while ((pos = reFile.indexIn(message, pos)) != -1)
        {
            pos += reFile.matchedLength();
            const QString uri = reFile.capturedTexts()[0];

            QString replace(uri);
            replace.remove("file:///", Qt::CaseInsensitive);
            replace.remove("file://", Qt::CaseInsensitive);

            QFileInfo fi(replace);
            if (fi.exists())
            {
#ifdef WIN32
                html.replace(uri, QString("<a href =\"file:///%1\">%1</a>").arg(fi.absoluteFilePath()));
#else
                html.replace(uri, QString("<a href =\"file://%1\">%1</a>").arg(fi.absoluteFilePath()));
#endif
            }
        }

        pos = 0;
        while ((pos = reMail.indexIn(message, pos)) != -1)
        {
            pos += reMail.matchedLength();
            const QString uri = reMail.capturedTexts()[0];

            QString replace(uri);
            replace.remove("mailto:", Qt::CaseInsensitive);

            html.replace(uri, QString("<a href =\"mailto:%1\">%1</a>").arg(replace));
        }
    }
    moveCursor(QTextCursor::End);
    insertHtml("<span style=\"color:" + m_colors[type] + "\">" + html + "</span><br>");

    ensureCursorVisible(); 
}

void MessageWidget::onAnchorClicked(const QUrl & link)
{
    QDesktopServices::openUrl(link);
}

void MessageWidget::setDetectLinks(bool enable)
{
    m_detectLinks = enable;
}

bool MessageWidget::detectLinks() const
{
    return m_detectLinks;
}

} // namespace widgetzeug
