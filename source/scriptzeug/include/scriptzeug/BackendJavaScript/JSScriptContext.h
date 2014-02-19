#pragma once


#include <v8.h>
#include <scriptzeug/Backend/AbstractScriptContext.h>


namespace scriptzeug
{


/** \brief JavaScript scripting context
 */
class SCRIPTZEUG_API JSScriptContext : public AbstractScriptContext
{
public:
    JSScriptContext();
    virtual ~JSScriptContext();

    virtual void registerObject(reflectionzeug::PropertyGroup * obj);
    virtual reflectionzeug::Variant evaluate(const std::string & code);

protected:
    void registerObj(v8::Handle<v8::Object> parent, reflectionzeug::PropertyGroup * obj);

protected:
    v8::Persistent<v8::Context>  m_context;
    v8::Isolate                 *m_isolate;
};


} // namespace scriptzeug
