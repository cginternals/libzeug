#pragma once

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/ScriptCompleter.h>


namespace widgetzeug
{

class WIDGETZEUG_API ECMA26251Completer : public ScriptCompleter
{
public:
    ECMA26251Completer();
    virtual ~ECMA26251Completer();
};

} // namespace widgetzeug
