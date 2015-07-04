#pragma once

#include "duktape-1.2.1/duktape.h"

#include <scriptzeug/backend/AbstractScriptContext.h>


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
    virtual void unregisterObject(reflectionzeug::PropertyGroup * obj);
    virtual reflectionzeug::Variant evaluate(const std::string & code);

protected:
    void registerObj(duk_idx_t parentId, reflectionzeug::PropertyGroup * obj);

protected:
    duk_context * m_context;
};


} // namespace scriptzeug
