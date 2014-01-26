#pragma once


#include <string>
#include <scriptzeug/Variant.h>


namespace zeug {
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

    virtual void registerObject(zeug::PropertyGroup * obj) = 0;
    virtual Variant evaluate(const std::string & code) = 0;
};


} // namespace zeug
