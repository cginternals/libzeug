#pragma once


#include <string>
#include <scriptzeug/Variant.h>


namespace reflectionzeug {
    class PropertyGroup;
}


namespace scriptzeug
{


/** \brief Base class for backend specific scripting contexts
 */
class SCRIPTZEUG_API AbstractScriptContext
{
public:
    AbstractScriptContext();
    virtual ~AbstractScriptContext();

    virtual void registerObject(reflectionzeug::PropertyGroup * obj) = 0;
    virtual Variant evaluate(const std::string & code) = 0;
};


} // namespace scriptzeug
