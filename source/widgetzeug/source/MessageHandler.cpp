
#include <widgetzeug/MessageHandler.h>

#include <cassert>

#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <QTextStream>

#include <widgetzeug/AbstractMessageReceiver.h>


namespace widgetzeug
{

MessageHandler * MessageHandler::m_instance = nullptr;


void globalMessageHandler(
    QtMsgType type
,   const QMessageLogContext & context
,   const QString & message)
{
    MessageHandler::instance()->handle(type, context, message);
}

MessageHandler * MessageHandler::instance()
{
    if(!m_instance)
        m_instance = new MessageHandler();

    return m_instance;
}

MessageHandler::MessageHandler(QObject * parent)
:    QObject(parent)
,    m_fstream(nullptr)
{
    printToConsole(true);
    printToFile(true);

    const QFileInfo fi(QCoreApplication::applicationFilePath());
    m_file.setFileName(QDir::tempPath() + QDir::separator() + fi.baseName() + ".log");
}

MessageHandler::~MessageHandler()
{
    if(m_fstream)
    {
        m_fstream->flush();
        delete m_fstream;
    }

    if(m_file.isOpen())
        m_file.close();
}

void MessageHandler::setFileName(const QString & fileName)
{
    QFile &file(instance()->m_file);

    if(file.isOpen())
    {
        file.rename(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
            qWarning("Could not open \"%s\" for message forwarding.", qPrintable(file.fileName()));
    }
    else
        file.setFileName(fileName);
}

const QString MessageHandler::fileName()
{
    return instance()->m_file.fileName();
}

QTextStream * MessageHandler::fstream()
{
    if(m_fstream)
    {
        assert(m_file.isOpen());
        return m_fstream;
    }

    if(!m_file.isOpen() && !m_file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qWarning("Could not open \"%s\" for message forwarding.", qPrintable(m_file.fileName()));
        return nullptr;
    }

    m_fstream = new QTextStream(&m_file);
    return m_fstream;
}

void MessageHandler::printToConsole(
    const bool enable)
{
    m_printToConsole[QtDebugMsg]    = enable;
    m_printToConsole[QtWarningMsg]  = enable;
    m_printToConsole[QtCriticalMsg] = enable;
    m_printToConsole[QtFatalMsg]    = enable;
}

void MessageHandler::printToFile(
    const bool enable)
{
    m_printToFile[QtDebugMsg]    = enable;
    m_printToFile[QtWarningMsg]  = enable;
    m_printToFile[QtCriticalMsg] = enable;
    m_printToFile[QtFatalMsg]    = enable;
}

void MessageHandler::setPrintToConsole(
    const bool enable)
{
    instance()->printToConsole(enable);
}

void MessageHandler::setPrintToConsole(
    const QtMsgType type
,   const bool enable)
{
    typedPrintFlags &flags(instance()->m_printToConsole);
    flags[type] = enable;
}

const bool MessageHandler::printsToConsole(const QtMsgType type)
{
    const typedPrintFlags &flags(instance()->m_printToConsole);
    if(!flags.contains(type))
        return false;

    return flags[type];
}

void MessageHandler::setPrintToFile(
    const bool enable)
{
    instance()->printToFile(enable);
}

void MessageHandler::setPrintToFile(
    const QtMsgType type
,   const bool enable)
{
    typedPrintFlags &flags(instance()->m_printToFile);
    flags[type] = enable;
}

const bool MessageHandler::printsToFile(const QtMsgType type)
{
    const typedPrintFlags &flags(instance()->m_printToFile);
    if(!flags.contains(type))
        return false;

    return flags[type];
}

void MessageHandler::handle(
    QtMsgType type
,   const QMessageLogContext & context
,   const QString & message)
{
    const QDateTime timestamp(QDateTime::currentDateTime());

    for (AbstractMessageReceiver * receiver : m_receivers)
        receiver->print(type, context, timestamp, message);

    // Early exit if no output is required.
    if(!printsToConsole(type)
    && !printsToFile(type))
        return;

    // Prepend appropriate message type hints.

    QString prefix("");

    switch (type) 
    {
    case QtWarningMsg:
        prefix = "Warning";  break;
    case QtCriticalMsg:
        prefix = "Critical"; break;
    case QtFatalMsg:
        prefix = "Fatal";    break;
    default:
        break;
    }

    QString output(message);

    if(!prefix.isEmpty() && !message.isEmpty())
        output.prepend(prefix + ": ");

    output.append("\n");

    printf(type, timestamp, output);
}

void MessageHandler::printf(
    QtMsgType type
,   const QDateTime & timestamp   
,   const QString & message)
{
    // Print to Console

    if(m_printToConsole[type])
        fputs(qPrintable(message), stderr);

    // Print to File

    if(m_printToFile[type] && fstream())
    {
        const QString t(timestamp.toString("yy-MM-dd::hh:mm:ss"));

        (*fstream()) << QString("[%1] %2").arg(t).arg(message);
        fstream()->flush();
    }    
}

void MessageHandler::attach(AbstractMessageReceiver & receiver)
{
    instance()->m_receivers.insert(&receiver);
}

void MessageHandler::dettach(AbstractMessageReceiver & receiver)
{
    instance()->m_receivers.remove(&receiver);
}

} // namespace widgetzeug
