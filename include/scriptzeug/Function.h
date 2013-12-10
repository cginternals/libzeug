#pragma once


#include <string>
#include <vector>
#include <functional>
#include <scriptzeug/Variant.h>


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

    virtual void call(const std::vector<Variant> & args) = 0;

protected:
    std::string m_name;
};


/** \brief Representation of a static function
 */
template <typename... Arguments>
class Function : public AbstractFunction
{
public:
    typedef std::function<void(Arguments...)> FuncType;

public:
    Function(const std::string & name, void (*fn)(Arguments...))
    : AbstractFunction(name)
    {
    }

    virtual ~Function()
    {
    }

    virtual void call(const std::vector<Variant> & args)
    {
    }
};


/** \brief Representation of a method
 */
template <class T, typename... Arguments>
class Method : public AbstractFunction
{
public:
    typedef std::function<void(Arguments...)> FuncType;

public:
    Method(const std::string & name, T * object, void (T::*method)(Arguments...))
    : AbstractFunction(name)
    {
    }

    virtual ~Method()
    {
    }

    virtual void call(const std::vector<Variant> & args)
    {
    }
};


} // namespace scriptzeug
