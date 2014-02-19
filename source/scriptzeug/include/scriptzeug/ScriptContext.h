#pragma once


#include <string>
#include <scriptzeug/Variant.h>


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
    ScriptContext(const std::string & backend = "javascript");
    virtual ~ScriptContext();

    void registerObject(reflectionzeug::PropertyGroup * obj);

    Variant evaluate(const std::string & code);

protected:
    AbstractScriptContext * m_backend;
};


} // namespace scriptzeug
