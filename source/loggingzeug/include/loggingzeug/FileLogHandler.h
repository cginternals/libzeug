#pragma once

#include <loggingzeug/loggingzeug_api.h>
#include <loggingzeug/AbstractLogHandler.h>
#include <loggingzeug/LogMessage.h>

namespace loggingzeug
{

/** \brief Writes LogMessages to a file (default: logfile.log).

	\see setLoggingHandler
	\see logging.h
*/
class LOGGINGZEUG_API FileLogHandler : public AbstractLogHandler
{
public:
    FileLogHandler(const std::string & logfile = "logfile.log");

    virtual void handle(const LogMessage & message) override;

protected:
    static std::string messagePrefix(const LogMessage & message);
    static std::string levelString(LogMessage::Level level);

    std::string m_logfile;
};

} // namespace loggingzeug
