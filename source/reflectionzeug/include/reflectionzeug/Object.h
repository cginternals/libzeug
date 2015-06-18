
#pragma once

#include <string>
#include <vector>

#include <reflectionzeug/function/Function.h>
#include <reflectionzeug/property/PropertyGroup.h>


namespace reflectionzeug
{


/**
*  @brief
*    Base class for reflectable classes that can expose properties and functions
*
*    To export one of your classes for automatic GUI generation and scripting, the
*    recommended usage is to inherit from Object and register your properties and
*    scripting functions in the constructor.
*/
class REFLECTIONZEUG_API Object : public PropertyGroup
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Object();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Name of object (for scripting and property access)
    */
    Object(const std::string & name);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Object();

    /**
    *  @brief
    *    Get list of functions exported by this object
    *
    *  @return
    *    List of functions
    */
    const std::vector<AbstractFunction *> & functions() const;

    /**
    *  @brief
    *    Add (export) function on object
    *
    *  @param[in] name
    *    Function name
    *  @param[in] fn
    *    Function pointer
    */
    template <typename RET, typename... Arguments>
    void addFunction(const std::string & name, RET (*fn)(Arguments...))
    {
        Function<RET, Arguments...> * func = new Function<RET, Arguments...>(name, fn);
        m_functions.push_back(func);
    }

    /**
    *  @brief
    *    Add (export) method on object
    *
    *  @param[in] name
    *    Function name
    *  @param[in] obj
    *    Pointer to object instance
    *  @param[in] member
    *    Method pointer
    */
    template <class T, typename RET, typename... Arguments>
    void addFunction(const std::string & name, T * obj, RET (T::*member)(Arguments...))
    {
        Method<T, RET, Arguments...> * method = new Method<T, RET, Arguments...>(name, obj, member);
        m_functions.push_back(method);
    }


protected:
    std::vector<AbstractFunction *> m_functions;    ///< List of exported functions
};


} // namespace reflectionzeug
