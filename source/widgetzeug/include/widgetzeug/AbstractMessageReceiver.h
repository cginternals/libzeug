#pragma once

#include <qglobal.h>

#include <widgetzeug/widgetzeug_api.h>

class QDateTime;
class QMessageContext;
class QString;

namespace widgetzeug
{

class WIDGETZEUG_API AbstractMessageReceiver
{
public:
    virtual void print(
        QtMsgType type
    ,   const QMessageLogContext & context
    ,   const QDateTime & timestamp
    ,   const QString & message) = 0;
};

} // namespace widgetzeug
