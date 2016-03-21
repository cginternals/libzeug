
#pragma once


#include "duktape-1.4.0/duktape.h"

#include <scriptzeug/backend/AbstractScriptContext.h>


namespace scriptzeug
{


/**
*  @brief
*    Duktape (Ecmascript) scripting backend
*/
class SCRIPTZEUG_API DuktapeScriptContext : public AbstractScriptContext
{
public:
    /**
    *  @brief
    *    Constructor
    */
    DuktapeScriptContext();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DuktapeScriptContext();

    // Virtual AbstractScriptContext functions
    virtual void initialize(ScriptContext * scriptContext) override;
    virtual void registerObject(reflectionzeug::PropertyGroup * obj) override;
    virtual void unregisterObject(reflectionzeug::PropertyGroup * obj) override;
    virtual reflectionzeug::Variant evaluate(const std::string & code) override;


protected:
    void registerObj(duk_idx_t parentId, reflectionzeug::PropertyGroup * obj);


protected:
    duk_context * m_context; ///< Duktape context
};


} // namespace scriptzeug
