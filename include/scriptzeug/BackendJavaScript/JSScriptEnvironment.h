#pragma once


#include <v8.h>
#include <scriptzeug/Backend/AbstractScriptEnvironment.h>


namespace scriptzeug
{


/** \brief JavaScript script environment
 */
class SCRIPTZEUG_API JSScriptEnvironment : public AbstractScriptEnvironment
{
public:
    JSScriptEnvironment();
    virtual ~JSScriptEnvironment();

    virtual void evaluate(const std::string & code);

protected:
    v8::Persistent<v8::Context> m_context;
};


} // namespace zeug
