#pragma once


#include <scriptzeug/Value.h>


namespace scriptzeug
{


/** \brief Template for parsing typed arguments from a list of variants
 */
template<typename T>
struct ArgValue {
    // Assume signed integral type by default
    static T get(std::vector<Value>::const_reverse_iterator &it, std::vector<Value>::const_reverse_iterator &end) {
        T value = 0;
        if (it != end) {
            value = (*it).toInt();
            ++it;
        }
        return value;
    }
};

/** \brief ArgValue specialization for type float
 */
template<>
struct ArgValue<float> {
    static float get(std::vector<Value>::const_reverse_iterator &it, std::vector<Value>::const_reverse_iterator &end) {
        double value = 0.0f;
        if (it != end) {
            value = (*it).toDouble();
            ++it;
        }
        return value;
    }
};

/** \brief ArgValue specialization for type double
 */
template<>
struct ArgValue<double> {
    static double get(std::vector<Value>::const_reverse_iterator &it, std::vector<Value>::const_reverse_iterator &end) {
        double value = 0.0f;
        if (it != end) {
            value = (*it).toDouble();
            ++it;
        }
        return value;
    }
};

/** \brief ArgValue specialization for type bool
 */
template<>
struct ArgValue<bool> {
    static bool get(std::vector<Value>::const_reverse_iterator &it, std::vector<Value>::const_reverse_iterator &end) {
        bool value = false;
        if (it != end) {
            value = (*it).toBool();
            ++it;
        }
        return value;
    }
};

/** \brief ArgValue specialization for type string
 */
template<>
struct ArgValue<std::string> {
    static std::string get(std::vector<Value>::const_reverse_iterator &it, std::vector<Value>::const_reverse_iterator &end) {
        std::string value;
        if (it != end) {
            value = (*it).toString();
            ++it;
        }
        return value;
    }
};


} // namespace scriptzeug
