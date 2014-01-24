#pragma once


#include <scriptzeug/Value.h>


namespace scriptzeug
{


/** \brief Template for parsing typed arguments from a list of variants
 */
template<typename T, size_t POS>
struct ArgValue {
    static T get(const std::vector<Value> & args) {
        // Assume signed integral type by default
        T value = 0;
        if (POS < args.size()) {
            value = args[POS].toInt();
        }
        return value;
    }
};

/** \brief ArgValue specialization for type float
 */
template<size_t POS>
struct ArgValue<float, POS> {
    static float get(const std::vector<Value> & args) {
        float value = 0.0f;
        if (POS < args.size()) {
            value = (float)args[POS].toDouble();
        }
        return value;
    }
};

/** \brief ArgValue specialization for type double
 */
template<size_t POS>
struct ArgValue<double, POS> {
    static double get(const std::vector<Value> & args) {
        double value = 0.0f;
        if (POS < args.size()) {
            value = args[POS].toDouble();
        }
        return value;
    }
};

/** \brief ArgValue specialization for type bool
 */
template<size_t POS>
struct ArgValue<bool, POS> {
    static bool get(const std::vector<Value> & args) {
        bool value = false;
        if (POS < args.size()) {
            value = args[POS].toBool();
        }
        return value;
    }
};

/** \brief ArgValue specialization for type string
 */
template<size_t POS>
struct ArgValue<std::string, POS> {
    static std::string get(const std::vector<Value> & args) {
        std::string value;
        if (POS < args.size()) {
            value = args[POS].toString();
        }
        return value;
    }
};

/** \brief ArgValue specialization for type Value
 */
template<size_t POS>
struct ArgValue<Value, POS> {
    static Value get(const std::vector<Value> & args) {
        Value value;
        if (POS < args.size()) {
            value = args[POS];
        }
        return value;
    }
};

/** \brief ArgValue specialization for type const Value &
 */
template<size_t POS>
struct ArgValue<const Value &, POS> {
    static Value get(const std::vector<Value> & args) {
        return ArgValue<Value, POS>::get(args);
    }
};

/** \brief ArgValue specialization for type const std::vector<Value> &
 */
template<size_t POS>
struct ArgValue<const std::vector<Value> &, POS> {
    static std::vector<Value> get(const std::vector<Value> & args) {
        std::vector<Value> list;
        for (size_t i=POS; i<args.size(); i++) {
            list.push_back(args[i]);
        }
        return list;
    }
};


/** \brief Sequence of numbers
 *         (e.g., Seq<0, 1, 2>)
 */
template<size_t... I>
struct Seq {};

/** \brief Sequence generator
 *         (e.g., GenSec<3>::Type = Seq<0, 1, 2>)
 */
template<int N, size_t... I>
struct GenSeq : GenSeq<N-1, N-1, I...> {};

template<size_t... I>
struct GenSeq<0, I...> { typedef Seq<I...> Type; };

/** \brief Pick type by index
 *         (e.g., PickType<1, void, int, float>::Type = int)
 */
template<size_t N, typename T, typename... Arguments>
struct PickType : PickType<N-1, Arguments...> {};

template<typename T, typename... Arguments>
struct PickType<0, T, Arguments...> { typedef T Type; };

/** \brief Generate ArgValue class for types and index
 *         (e.g., ArgValueGen<2, float, int, double>::Type = ArgValue<int, 2>
 */
template<size_t I, typename... Arguments>
struct ArgValueGen {
    typedef typename PickType<I, Arguments...>::Type T;
    typedef ArgValue<T, I>                           Type;
};

/** \brief Template for calling a static function with a return value
 */
template <typename RET, typename... Arguments>
class CallFunction
{
public:
    typedef RET (*FuncPtr) (Arguments...);

    static Value call(FuncPtr func, Arguments... args) {
        return Value( (*func)(args...) );
    }
};

/** \brief Template for calling a static function without a return value
 */
template <typename... Arguments>
class CallFunction<void, Arguments...>
{
public:
    typedef void (*FuncPtr) (Arguments...);

    static Value call(FuncPtr func, Arguments... args) {
        (*func)(args...);
        return Value();
    }
};

/** \brief Template for calling a member function with a return value
 */
template <typename T, typename RET, typename... Arguments>
class CallMethod
{
public:
    typedef RET (T::*MethodPtr) (Arguments...);

    static Value call(T * obj, MethodPtr method, Arguments... args) {
        return Value( (obj->*method)(args...) );
    }
};

/** \brief Template for calling a member function without a return value
 */
template <typename T, typename... Arguments>
class CallMethod<T, void, Arguments...>
{
public:
    typedef void (T::*MethodPtr) (Arguments...);

    static Value call(T * obj, MethodPtr method, Arguments... args) {
        (obj->*method)(args...);
        return Value();
    }
};


} // namespace scriptzeug
