
#include <widgetzeug/ECMA26251_Completer.h>

#include <QString>

namespace widgetzeug
{

namespace
{
    // http://www.ecma-international.org/ecma-262/5.1/

    const QStringList ECMA_Keywords = QStringList() 
        << "break"
        << "case"
        << "catch"
        << "continue"
        << "debugger"
        << "default"
        << "delete"
        << "do"
        << "else"
        << "finally"
        << "for"
        << "function"
        << "if"
        << "in"
        << "instanceof"
        << "new"
        << "return"
        << "switch"
        << "this"
        << "throw"
        << "try"
        << "typeof"
        << "var"
        << "void"
        << "while"
        << "with";
}

ECMA26251Completer::ECMA26251Completer()
{
    registerWords(ECMA_Keywords);
}

ECMA26251Completer::~ECMA26251Completer()
{
}

} // namespace widgetzeug
