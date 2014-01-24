#pragma once


#include <string>
#include <scriptzeug/Value.h>


namespace zeug {
    class PropertyGroup;
}


namespace scriptzeug
{


/** \brief Base class for backend specific script environments
 */
class SCRIPTZEUG_API AbstractScriptEnvironment
{
public:
    AbstractScriptEnvironment();
    virtual ~AbstractScriptEnvironment();

    virtual void registerObject(zeug::PropertyGroup * obj) = 0;
    virtual Value evaluate(const std::string & code) = 0;
};


} // namespace zeug
