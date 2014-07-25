#include <loggingzeug/logging.h>

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

LogMessageBuilder info(const std::string & context, LogMessage::Level level)
{
    return LogMessageBuilder(level, level <= l_verbosityLevel ? l_logHandler : nullptr, context);
}

LogMessageBuilder debug(const std::string & context)
{
    return info(context, LogMessage::Debug);
}

LogMessageBuilder warning(const std::string & context)
{
    return info(context, LogMessage::Warning);
}

LogMessageBuilder critical(const std::string & context)
{
    return info(context, LogMessage::Critical);
}

LogMessageBuilder fatal(const std::string & context)
{
    return info(context, LogMessage::Fatal);
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
