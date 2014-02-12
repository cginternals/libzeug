#pragma once


#include <string>
#include <vector>
#include <functional>
#include <scriptzeug/Variant.h>
#include <scriptzeug/TemplateHelper.h>


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

    virtual Variant call(const std::vector<Variant> & args) = 0;

protected:
    std::string m_name;
};


/** \brief Representation of a static function
 */
template <typename RET, typename... Arguments>
class Function : public AbstractFunction
{
public:
    typedef RET (*FuncPtr) (Arguments...);

public:
    Function(const std::string & name, FuncPtr func)
    : AbstractFunction(name)
    , m_func(func)
    {
    }

    virtual ~Function()
    {
    }

    virtual Variant call(const std::vector<Variant> & args)
    {
        return callFunction(typename GenSeq<sizeof...(Arguments)>::Type(), args);
    }

protected:
    template<size_t... I>
    Variant callFunction(Seq<I...>, const std::vector<Variant> & args)
    {
        return CallFunction<RET, Arguments...>::call(m_func, ArgValueGen<I, Arguments...>::Type::get(args)...);
    }

protected:
    FuncPtr m_func;
};


/** \brief Representation of a method
 */
template <class T, typename RET, typename... Arguments>
class Method : public AbstractFunction
{
public:
    typedef RET (T::*MethodPtr) (Arguments...);

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

    virtual Variant call(const std::vector<Variant> & args)
    {
        return callMethod(typename GenSeq<sizeof...(Arguments)>::Type(), args);
    }

protected:
    template<size_t... I>
    Variant callMethod(Seq<I...>, const std::vector<Variant> & args)
    {
        return CallMethod<T, RET, Arguments...>::call(m_obj, m_method, ArgValueGen<I, Arguments...>::Type::get(args)...);
    }

protected:
    MethodPtr   m_method;
    T         * m_obj;
};


} // namespace scriptzeug
