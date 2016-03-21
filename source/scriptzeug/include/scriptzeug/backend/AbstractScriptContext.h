
#pragma once


#include <string>

#include <reflectionzeug/variant/Variant.h>

#include <scriptzeug/scriptzeug_api.h>


namespace reflectionzeug {
    class PropertyGroup;
}


namespace scriptzeug
{


class ScriptContext;


/**
*  @brief
*    Base class for scripting context backends
*/
class SCRIPTZEUG_API AbstractScriptContext
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractScriptContext();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractScriptContext();

    /**
    *  @brief
    *    Initialize scripting backend
    *
    *  @param[in] scriptContext
    *    Script context that owns the backend (must NOT be null)
    *
    *  @remarks
    *    Be sure to assign the script context to m_scriptContext.
    */
    virtual void initialize(ScriptContext * scriptContext) = 0;

    /**
    *  @brief
    *    Expose object to scripting
    *
    *  @param[in] obj
    *    Object to be exposed for scripting (must NOT be null)
    */
    virtual void registerObject(reflectionzeug::PropertyGroup * obj) = 0;

    /**
    *  @brief
    *    Remove object from scripting
    *
    *  @param[in] obj
    *    Object to be removed from scripting (must NOT be null)
    */
    virtual void unregisterObject(reflectionzeug::PropertyGroup * obj) = 0;

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
    virtual reflectionzeug::Variant evaluate(const std::string & code) = 0;


protected:
	ScriptContext * m_scriptContext; ///< Script context holding this backend
};


} // namespace scriptzeug
