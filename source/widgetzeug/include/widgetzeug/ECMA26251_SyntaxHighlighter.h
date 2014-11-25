#pragma once

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/ScriptSyntaxHighlighter.h>


namespace widgetzeug
{

class WIDGETZEUG_API ECMA26251SyntaxHighlight : public ScriptSyntaxHighlighter
{
public:
    ECMA26251SyntaxHighlight();
    virtual ~ECMA26251SyntaxHighlight();
};

} // namespace widgetzeug
