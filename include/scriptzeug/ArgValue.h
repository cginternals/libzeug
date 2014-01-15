#pragma once


#include <scriptzeug/Variant.h>


namespace scriptzeug
{


/** \brief Template for parsing typed arguments from dynamic variant lists
 */
template<typename T>
struct ArgValue {
};


/** \brief ArgValue specialization for type int
 */
template<>
struct ArgValue<int> {
    static int get(std::vector<Variant>::const_iterator &it, std::vector<Variant>::const_iterator &end) {
        int value = 0;
        if (it != end) {
            value = (*it).intValue();
            ++it;
        }
        return value;
    }
};


/** \brief ArgValue specialization for type float
 */
template<>
struct ArgValue<float> {
    static float get(std::vector<Variant>::const_iterator &it, std::vector<Variant>::const_iterator &end) {
        float value = 0.0f;
        if (it != end) {
            value = (*it).floatValue();
            ++it;
        }
        return value;
    }
};


/** \brief ArgValue specialization for type string
 */
template<>
struct ArgValue<std::string> {
    static std::string get(std::vector<Variant>::const_iterator &it, std::vector<Variant>::const_iterator &end) {
        std::string value;
        if (it != end) {
            value = (*it).stringValue();
            ++it;
        }
        return value;
    }
};


} // namespace scriptzeug
