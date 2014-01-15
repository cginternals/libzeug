#pragma once


#include <string>
#include <vector>
#include <functional>
#include <scriptzeug/ArgValue.h>


namespace scriptzeug
{


/** \brief Base class for representing functions
 */
class AbstractFunction
{
public:
    AbstractFunction(const std::string & name) :
    m_name(name)
    {
    }

    virtual ~AbstractFunction()
    {
    }

    std::string name() const
    {
        return m_name;
    }

    virtual void call(const std::vector<Value> & args) = 0;

protected:
    std::string m_name;
};


/** \brief Representation of a static function
 */
template <typename... Arguments>
class Function : public AbstractFunction
{
public:
    typedef void (*FuncPtr) (Arguments...);

public:
    Function(const std::string & name, FuncPtr func)
    : AbstractFunction(name)
    , m_func(func)
    {
    }

    virtual ~Function()
    {
    }

    virtual void call(const std::vector<Value> & args)
    {
        // Get arguments
        std::vector<Value>::const_reverse_iterator it  = args.rbegin();
        std::vector<Value>::const_reverse_iterator end = args.rend();

        // Check for wrong number of arguments
        size_t numArgs  = sizeof...(Arguments);
        size_t numFound = args.size();
        size_t numEmpty = 0;
        if (numFound > numArgs) {
            // Skip additional arguments
            for (size_t i=numArgs; i<numFound; i++)
                it++;
        } else if (numArgs > numFound) {
            numEmpty = numArgs - numFound;
        }

        // Call function
        (*m_func)(ArgValue<Arguments>::get(it, end, numEmpty)...);
    }

protected:
    FuncPtr m_func;
};


/** \brief Representation of a method
 */
template <class T, typename... Arguments>
class Method : public AbstractFunction
{
public:
    typedef void (T::*MethodPtr) (Arguments...);

public:
    Method(const std::string & name, T * obj, MethodPtr method)
    : AbstractFunction(name)
    , m_method(method)
    , m_obj(obj)
    {
    }

    virtual ~Method()
    {
    }

    virtual void call(const std::vector<Value> & args)
    {
        // Get arguments
        std::vector<Value>::const_reverse_iterator it  = args.rbegin();
        std::vector<Value>::const_reverse_iterator end = args.rend();

        // Check for wrong number of arguments
        size_t numArgs  = sizeof...(Arguments);
        size_t numFound = args.size();
        size_t numEmpty = 0;
        if (numFound > numArgs) {
            // Skip additional arguments
            for (size_t i=numArgs; i<numFound; i++)
                it++;
        } else if (numArgs > numFound) {
            numEmpty = numArgs - numFound;
        }

        // Call function
        (m_obj->*m_method) ( ArgValue<Arguments>::get(it, end, numEmpty)... );
    }

protected:
    MethodPtr   m_method;
    T         * m_obj;
};


} // namespace scriptzeug
