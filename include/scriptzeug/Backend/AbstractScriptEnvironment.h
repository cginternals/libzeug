#pragma once


#include <string>
#include <scriptzeug/scriptzeug.h>


namespace scriptzeug
{


/** \brief Base class for backend specific script environments
 */
class SCRIPTZEUG_API AbstractScriptEnvironment
{
public:
    AbstractScriptEnvironment();
    virtual ~AbstractScriptEnvironment();

    virtual void evaluate(const std::string & code) = 0;
};


} // namespace zeug
