#include <loggingzeug/baselogging.h>

#include <cassert>

#include <loggingzeug/AbstractLogHandler.h>
#include <loggingzeug/LogMessageBuilder.h>
#include <loggingzeug/ConsoleLogHandler.h>

namespace
{
    loggingzeug::LogMessage::Level l_verbosityLevel = loggingzeug::LogMessage::Info;
    loggingzeug::AbstractLogHandler * l_logHandler = new loggingzeug::ConsoleLogHandler();
}

namespace loggingzeug
{

LogMessageBuilder info(LogMessage::Level level)
{
    return LogMessageBuilder(level, level <= l_verbosityLevel ? l_logHandler : nullptr);
}

LogMessageBuilder debug()
{
    return info(LogMessage::Debug);
}

LogMessageBuilder warning()
{
    return info(LogMessage::Warning);
}

LogMessageBuilder critical()
{
    return info(LogMessage::Critical);
}

LogMessageBuilder fatal()
{
    return info(LogMessage::Fatal);
}

AbstractLogHandler * loggingHandler()
{
    return l_logHandler;
}

void setLoggingHandler(AbstractLogHandler* handler)
{
    delete l_logHandler;
    l_logHandler = handler;
}

void setVerbosityLevel(LogMessage::Level verbosity)
{
    l_verbosityLevel = verbosity;
}

LogMessage::Level verbosityLevel()
{
    return l_verbosityLevel;
}

} // namespace loggingzeug
