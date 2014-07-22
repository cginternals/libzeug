#pragma once

#include <loggingzeug/loggingzeug_api.h>
#include <loggingzeug/AbstractLogHandler.h>
#include <loggingzeug/LogMessage.h>

namespace loggingzeug
{

/** \brief Writes LogMessages to stdout.

	This is the default LogMessage handler of loggingzeug.

	\see setLoggingHandler
	\see logging.h
*/
class LOGGINGZEUG_API ConsoleLogHandler : public AbstractLogHandler
{
public:
    virtual void handle(const LogMessage & message) override;

protected:
    static std::string messagePrefix(const LogMessage & message);
    static std::string levelString(LogMessage::Level level);
};

} // namespace loggingzeug
