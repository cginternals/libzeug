#pragma once


#include <string>
#include <vector>
#include <propertyzeug/PropertyGroup.h>
#include "scriptzeug/Function.h"


namespace scriptzeug
{


/** \brief Base class for classes that expose a scripting interface
 */
class SCRIPTZEUG_API Scriptable : public zeug::PropertyGroup
{
public:
    Scriptable(const std::string & name);
    virtual ~Scriptable();

    const std::vector<AbstractFunction *> & functions() const;

    template <typename RET, typename... Arguments>
    void addFunction(const std::string & name, RET (*fn)(Arguments...))
    {
        Function<RET, Arguments...> * func = new Function<RET, Arguments...>(name, fn);
        m_functions.push_back(func);
    }

    template <class T, typename RET, typename... Arguments>
    void addFunction(const std::string & name, T * obj, RET (T::*member)(Arguments...))
    {
        Method<T, RET, Arguments...> * method = new Method<T, RET, Arguments...>(name, obj, member);
        m_functions.push_back(method);
    }

protected:
    std::vector<AbstractFunction *> m_functions;
};


} // namespace scriptzeug
