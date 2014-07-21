#pragma once

#include <loggingzeug/loggingzeug_api.h>

#include <loggingzeug/LogMessage.h>
#include <loggingzeug/LogMessageBuilder.h>

namespace loggingzeug
{

class AbstractLogHandler;
class LogMessageBuilder;

/**
  * Creates a stream like object (LogMessageBuilder) to create a LogMessage from the objects
  * passed to it and sends the LogMessage to the global LogMessageHandler when the builder goes out of scope.
  * Similar to `qDebug()` from Qt.
  *
  * \code{.cpp}
  * info() << "Message: " << 3.14;
  * \endcode
  */
LOGGINGZEUG_API LogMessageBuilder info(LogMessage::Level level = LogMessage::Info);
LOGGINGZEUG_API LogMessageBuilder debug();
LOGGINGZEUG_API LogMessageBuilder warning();
LOGGINGZEUG_API LogMessageBuilder critical();
LOGGINGZEUG_API LogMessageBuilder fatal();

LOGGINGZEUG_API void setLoggingHandler(AbstractLogHandler * handler);
LOGGINGZEUG_API AbstractLogHandler * loggingHandler();

LOGGINGZEUG_API void setVerbosityLevel(LogMessage::Level verbosity);
LOGGINGZEUG_API LogMessage::Level verbosityLevel();

/**
 * Uses formatString to write on the usual logging streams.
 *
 *  Sample usage:
 *  \code{.cpp}
 *      info("This is a test: %; pi = %+0E10.5;", 42, 3.141592653589793); // output: "This is a test: 42 pi = +3.14159E+00"
 *      info("%; - %X; - %rf?_10.2;", "a string", 255, 2.71828182846); // output: "a string - 255 - ______2.72"
 *  \endcode
 *
 *   \see formatString
 */
template <typename... Arguments>
void info(const char* format, Arguments... arguments);

/**
 *  \see info
 */
template <typename... Arguments>
void debug(const char* format, Arguments... arguments);

/**
 *  \see info
 */
template <typename... Arguments>
void warning(const char* format, Arguments... arguments);

/**
 *  \see info
 */
template <typename... Arguments>
void critical(const char* format, Arguments... arguments);

/**
 *  \see info
 */
template <typename... Arguments>
void fatal(const char* format, Arguments... arguments);

} // namespace loggingzeug

#include <loggingzeug/baselogging.hpp>
