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
        callFunction(typename GenSeq<sizeof...(Arguments)>::Type(), args);
    }

protected:
    template<size_t... I>
    void callFunction(Seq<I...>, const std::vector<Value> & args)
    {
        (*m_func)(ArgValueGen<I, Arguments...>::Type::get(args)...);
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
        callMethod(typename GenSeq<sizeof...(Arguments)>::Type(), args);
    }

protected:
    template<size_t... I>
    void callMethod(Seq<I...>, const std::vector<Value> & args)
    {
        (m_obj->*m_method)(ArgValueGen<I, Arguments...>::Type::get(args)...);
    }

protected:
    MethodPtr   m_method;
    T         * m_obj;
};


} // namespace scriptzeug
