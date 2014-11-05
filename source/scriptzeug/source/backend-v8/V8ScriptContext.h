#pragma once


#include <v8.h>
#include <scriptzeug/backend/AbstractScriptContext.h>


namespace scriptzeug
{


/** \brief V8 (Ecmascript) scripting context
 */
class SCRIPTZEUG_API V8ScriptContext : public AbstractScriptContext
{
public:
    V8ScriptContext(ScriptContext * scriptContext);
    virtual ~V8ScriptContext();

    virtual void registerObject(reflectionzeug::PropertyGroup * obj);
    virtual reflectionzeug::Variant evaluate(const std::string & code);

protected:
    void registerObj(v8::Handle<v8::Object> parent, reflectionzeug::PropertyGroup * obj);

protected:
    v8::Persistent<v8::Context>  m_context;
    v8::Isolate                 *m_isolate;
};


} // namespace scriptzeug
