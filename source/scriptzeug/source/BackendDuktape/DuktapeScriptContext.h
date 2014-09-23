#pragma once


#include "duktape-0.11.0/duktape.h"
#include <scriptzeug/Backend/AbstractScriptContext.h>


namespace scriptzeug
{


/** \brief Duktape (Ecmascript) scripting context
 */
class SCRIPTZEUG_API DuktapeScriptContext : public AbstractScriptContext
{
public:
    DuktapeScriptContext(ScriptContext * scriptContext);
    virtual ~DuktapeScriptContext();

    virtual void registerObject(reflectionzeug::PropertyGroup * obj);
    virtual reflectionzeug::Variant evaluate(const std::string & code);

protected:
    duk_context * m_context;
};


} // namespace scriptzeug
