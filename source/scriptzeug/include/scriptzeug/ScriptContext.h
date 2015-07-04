#pragma once


#include <string>

#include <signalzeug/Signal.h>

#include <reflectionzeug/variant/Variant.h>

#include <scriptzeug/scriptzeug_api.h>


namespace reflectionzeug {
    class PropertyGroup;
}


namespace scriptzeug
{


class AbstractScriptContext;


/** \brief The entry point to managing scripting in your application
 */
class SCRIPTZEUG_API ScriptContext
{
public:
    signalzeug::Signal<const std::string &> scriptException;

public:
    ScriptContext(const std::string & backend = "javascript");
    virtual ~ScriptContext();

    void registerObject(reflectionzeug::PropertyGroup * obj);
    void unregisterObject(reflectionzeug::PropertyGroup * obj);

    reflectionzeug::Variant evaluate(const std::string & code);

protected:
    AbstractScriptContext * m_backend;
};


} // namespace scriptzeug
