#pragma once


#include <string>
#include <vector>
#include <functional>
#include <scriptzeug/Variant.h>


namespace scriptzeug
{


template <typename... Arguments>
class Cascade
{
public:
    typedef std::function<void(Arguments...)> Callback;

    static void call(std::vector<Variant>::const_iterator it, Callback cb)
    {
        cb();
    }
};

template <typename... Arguments>
class Cascade<int, Arguments...>
{
public:
    typedef std::function<void(int, Arguments...)> Callback;

    static void call(std::vector<Variant>::const_iterator it, Callback cb)
    {
        int value = (*it).intValue();
        Cascade<Arguments...>::call(it+1, [cb, value] (Arguments... arguments) {
            cb(value, arguments...);
        });
    }
};

template <typename... Arguments>
class Cascade<float, Arguments...>
{
public:
    typedef std::function<void(float, Arguments...)> Callback;

    static void call(std::vector<Variant>::const_iterator it, Callback cb)
    {
        float value = (*it).floatValue();
        Cascade<Arguments...>::call(it+1, [cb, value] (Arguments... arguments) {
            cb(value, arguments...);
        });
    }
};

template <typename... Arguments>
class Cascade<std::string, Arguments...>
{
public:
    typedef std::function<void(const std::string &, Arguments...)> Callback;

    static void call(std::vector<Variant>::const_iterator it, Callback cb)
    {
        std::string value = (*it).stringValue();
        Cascade<Arguments...>::call(it+1, [cb, value] (Arguments... arguments) {
            cb(value, arguments...);
        });
    }
};


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

    virtual void call(const std::vector<Variant> & args)
    {
        Cascade< Arguments... >::call(args.begin(), [this] (Arguments... arguments) {
            (*m_func)(arguments...);
        });
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

    virtual void call(const std::vector<Variant> & args)
    {
        Cascade< Arguments... >::call(args.begin(), [this] (Arguments... arguments) {
            (m_obj->*m_method)(arguments...);
        });
    }

protected:
    MethodPtr   m_method;
    T         * m_obj;
};


} // namespace scriptzeug
