
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


/**
*  @brief
*    The entry point to managing scripting in your application
*/
class SCRIPTZEUG_API ScriptContext
{
public:
    /**
    *  @brief
    *    Called when a script triggered an exception
    */
    signalzeug::Signal<const std::string &> scriptException;


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] backend
    *    Name of the backend (supported: "javascript")
    */
    ScriptContext(const std::string & backend = "javascript");

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] backend
    *    Scripting backend (must NOT be null)
    */
    ScriptContext(AbstractScriptContext * backend);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ScriptContext();

    /**
    *  @brief
    *    Set global namespace
    *
    *  @param[in] name
    *    Namespace at which global objects are registered
    *
    *  @remarks
    *    If set, objects are not registered globally but into
    *    an object with the given name. E.g., if the global
    *    namespace is 'myapp', registerObject(obj) can be
    *    accessed via 'myapp.obj' instead of 'obj'.
    *
    *    Some backends, such as the Qml scripting backend,
    *    may require a global namespace, since they do not
    *    allow to modify the global object. In this case,
    *    setGlobalNamespace() can be used to make other
    *    backends compatible.
    */
    void setGlobalNamespace(const std::string & name);

    /**
    *  @brief
    *    Expose object to scripting
    *
    *  @param[in] obj
    *    Object to be exposed for scripting (must NOT be null)
    */
    void registerObject(reflectionzeug::PropertyGroup * obj);

    /**
    *  @brief
    *    Remove object from scripting
    *
    *  @param[in] obj
    *    Object to be removed from scripting (must NOT be null)
    */
    void unregisterObject(reflectionzeug::PropertyGroup * obj);

    /**
    *  @brief
    *    Execute script
    *
    *  @param[in] code
    *    Scripting code
    *
    *  @return
    *    Return value of the executed code
    */
    reflectionzeug::Variant evaluate(const std::string & code);


protected:
    AbstractScriptContext * m_backend;  ///< Scripting backend
};


} // namespace scriptzeug
