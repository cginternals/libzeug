#pragma once


#include <string>
#include <scriptzeug/Value.h>


namespace scriptzeug
{


class AbstractScriptEnvironment;
class Scriptable;


/** \brief The entry point to managing a scripting engine in your application
 */
class SCRIPTZEUG_API ScriptEnvironment
{
public:
    ScriptEnvironment(const std::string & backend = "javascript");
    virtual ~ScriptEnvironment();

    void registerObject(const std::string & name, Scriptable * obj);

    Value evaluate(const std::string & code);

protected:
    AbstractScriptEnvironment * m_backend;
};


} // namespace zeug
