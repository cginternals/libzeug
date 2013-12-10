#pragma once


#include <string>
#include <vector>
#include <scriptzeug/Function.h>


namespace scriptzeug
{


/** \brief Base class for classes that expose a scripting interface
 */
class SCRIPTZEUG_API Scriptable
{
public:
    Scriptable();
    virtual ~Scriptable();

    const std::vector<AbstractFunction *> & functions() const;

    template <typename... Arguments>
    void addFunction(const std::string & name, void (*fn)(Arguments...))
    {
        Function<Arguments...> * func = new Function<Arguments...>(name, fn);
        m_functions.push_back(func);
    }

    template <class T, typename... Arguments>
    void addFunction(const std::string & name, T * obj, void (T::*member)(Arguments...))
    {
        Method<T, Arguments...> * method = new Method<T, Arguments...>(name, obj, member);
        m_functions.push_back(method);
    }

protected:
    std::vector<AbstractFunction *> m_functions;
};


} // namespace scriptzeug
