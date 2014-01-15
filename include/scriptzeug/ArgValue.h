#pragma once


#include <scriptzeug/Value.h>


namespace scriptzeug
{


/** \brief Template for parsing typed arguments from a list of variants
 */
template<typename T>
struct ArgValue {
    // Assume signed integral type by default
    static T get(std::vector<Value>::const_reverse_iterator &it, std::vector<Value>::const_reverse_iterator &end, size_t & numEmpty) {
        T value = 0;
        if (numEmpty == 0 && it != end) {
            value = (*it).toInt();
            ++it;
        }
        if (numEmpty > 0) numEmpty--;
        return value;
    }
};

/** \brief ArgValue specialization for type float
 */
template<>
struct ArgValue<float> {
    static float get(std::vector<Value>::const_reverse_iterator &it, std::vector<Value>::const_reverse_iterator &end, size_t & numEmpty) {
        double value = 0.0f;
        if (numEmpty == 0 && it != end) {
            value = (*it).toDouble();
            ++it;
        }
        if (numEmpty > 0) numEmpty--;
        return value;
    }
};

/** \brief ArgValue specialization for type double
 */
template<>
struct ArgValue<double> {
    static double get(std::vector<Value>::const_reverse_iterator &it, std::vector<Value>::const_reverse_iterator &end, size_t & numEmpty) {
        double value = 0.0f;
        if (numEmpty == 0 && it != end) {
            value = (*it).toDouble();
            ++it;
        }
        if (numEmpty > 0) numEmpty--;
        return value;
    }
};

/** \brief ArgValue specialization for type bool
 */
template<>
struct ArgValue<bool> {
    static bool get(std::vector<Value>::const_reverse_iterator &it, std::vector<Value>::const_reverse_iterator &end, size_t & numEmpty) {
        bool value = false;
        if (numEmpty == 0 && it != end) {
            value = (*it).toBool();
            ++it;
        }
        if (numEmpty > 0) numEmpty--;
        return value;
    }
};

/** \brief ArgValue specialization for type string
 */
template<>
struct ArgValue<std::string> {
    static std::string get(std::vector<Value>::const_reverse_iterator &it, std::vector<Value>::const_reverse_iterator &end, size_t & numEmpty) {
        std::string value;
        if (numEmpty == 0 && it != end) {
            value = (*it).toString();
            ++it;
        }
        if (numEmpty > 0) numEmpty--;
        return value;
    }
};

/** \brief ArgValue specialization for type scriptzeug::Value
 */
template<>
struct ArgValue<scriptzeug::Value> {
    static scriptzeug::Value get(std::vector<Value>::const_reverse_iterator &it, std::vector<Value>::const_reverse_iterator &end, size_t & numEmpty) {
        scriptzeug::Value value;
        if (numEmpty == 0 && it != end) {
            value = *it;
            ++it;
        }
        if (numEmpty > 0) numEmpty--;
        return value;
    }
};

/** \brief ArgValue specialization for type const scriptzeug::Value &
 */
template<>
struct ArgValue<const scriptzeug::Value &> {
    static scriptzeug::Value get(std::vector<Value>::const_reverse_iterator &it, std::vector<Value>::const_reverse_iterator &end, size_t & numEmpty) {
        return ArgValue<scriptzeug::Value>::get(it, end, numEmpty);
    }
};


} // namespace scriptzeug
