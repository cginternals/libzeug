#pragma once


#include <string>
#include <scriptzeug/scriptzeug.h>


namespace scriptzeug
{


class Scriptable;


/** \brief Base class for backend specific script environments
 */
class SCRIPTZEUG_API AbstractScriptEnvironment
{
public:
    AbstractScriptEnvironment();
    virtual ~AbstractScriptEnvironment();

    virtual void registerObject(const std::string & name, Scriptable * obj) = 0;
    virtual void evaluate(const std::string & code) = 0;
};


} // namespace zeug
