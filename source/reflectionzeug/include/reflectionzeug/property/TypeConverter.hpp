
#pragma once


#include <reflectionzeug/property/TypeConverter.h>

#include <sstream>


namespace reflectionzeug
{


// Type conversion for primitive data types
template <typename Type>
PrimitiveTypeConverter<Type>::PrimitiveTypeConverter()
{
}

template <typename Type>
PrimitiveTypeConverter<Type>::~PrimitiveTypeConverter()
{
}

template <typename Type>
bool PrimitiveTypeConverter<Type>::canConvert(const std::type_info & targetType) const
{
    if (targetType == typeid(bool) ||
        targetType == typeid(char) ||
        targetType == typeid(unsigned char) ||
        targetType == typeid(short) ||
        targetType == typeid(unsigned short) ||
        targetType == typeid(int) ||
        targetType == typeid(unsigned int) ||
        targetType == typeid(long) ||
        targetType == typeid(unsigned long) ||
        targetType == typeid(long long) ||
        targetType == typeid(unsigned long long) ||
        targetType == typeid(float) ||
        targetType == typeid(double) ||
        targetType == typeid(std::string) )
    {
        return true;
    } else {
        return false;
    }
}

template <typename Type>
bool PrimitiveTypeConverter<Type>::convert(const Type & value, void * target, const std::type_info & targetType) const
{
    if (targetType == typeid(bool)) {
        *reinterpret_cast<bool *>(target) = (bool)value;
    } else if (targetType == typeid(char)) {
        *reinterpret_cast<char *>(target) = (char)value;
    } else if (targetType == typeid(unsigned char)) {
        *reinterpret_cast<unsigned char *>(target) = (unsigned char)value;
    } else if (targetType == typeid(short)) {
        *reinterpret_cast<short *>(target) = (short)value;
    } else if (targetType == typeid(unsigned short)) {
        *reinterpret_cast<unsigned short *>(target) = (unsigned short)value;
    } else if (targetType == typeid(int)) {
        *reinterpret_cast<int *>(target) = (int)value;
    } else if (targetType == typeid(unsigned int)) {
        *reinterpret_cast<unsigned int *>(target) = (unsigned int)value;
    } else if (targetType == typeid(long)) {
        *reinterpret_cast<long *>(target) = (long)value;
    } else if (targetType == typeid(unsigned long)) {
        *reinterpret_cast<unsigned long *>(target) = (unsigned long)value;
    } else if (targetType == typeid(long long)) {
        *reinterpret_cast<long long *>(target) = (long long)value;
    } else if (targetType == typeid(unsigned long long)) {
        *reinterpret_cast<unsigned long long *>(target) = (unsigned long long)value;
    } else if (targetType == typeid(float)) {
        *reinterpret_cast<float *>(target) = (float)value;
    } else if (targetType == typeid(double)) {
        *reinterpret_cast<double *>(target) = (double)value;
    } else if (targetType == typeid(std::string)) {
        std::stringstream s;
        s << value;
        *reinterpret_cast<std::string *>(target) = s.str();
    } else {
        return false;
    }

    return true;
}


// Type conversion for string data types
template <typename Type>
StringConverter<Type>::StringConverter()
{
}

template <typename Type>
StringConverter<Type>::~StringConverter()
{
}

template <typename Type>
bool StringConverter<Type>::canConvert(const std::type_info & targetType) const
{
    if (targetType == typeid(bool) ||
        targetType == typeid(char) ||
        targetType == typeid(unsigned char) ||
        targetType == typeid(short) ||
        targetType == typeid(unsigned short) ||
        targetType == typeid(int) ||
        targetType == typeid(unsigned int) ||
        targetType == typeid(long) ||
        targetType == typeid(unsigned long) ||
        targetType == typeid(long long) ||
        targetType == typeid(unsigned long long) ||
        targetType == typeid(float) ||
        targetType == typeid(double) ||
        targetType == typeid(std::string) )
    {
        return true;
    } else {
        return false;
    }
}

template <typename Type>
bool StringConverter<Type>::convert(const Type & value, void * target, const std::type_info & targetType) const
{
    if (targetType == typeid(bool)) {
        int & v = *reinterpret_cast<int *>(target);
        std::istringstream(value) >> v;
    } else if (targetType == typeid(char)) {
        char & v = *reinterpret_cast<char *>(target);
        std::istringstream(value) >> v;
    } else if (targetType == typeid(unsigned char)) {
        unsigned char & v = *reinterpret_cast<unsigned char *>(target);
        std::istringstream(value) >> v;
    } else if (targetType == typeid(short)) {
        short & v = *reinterpret_cast<short *>(target);
        std::istringstream(value) >> v;
    } else if (targetType == typeid(unsigned short)) {
        unsigned short & v = *reinterpret_cast<unsigned short *>(target);
        std::istringstream(value) >> v;
    } else if (targetType == typeid(int)) {
        int & v = *reinterpret_cast<int *>(target);
        std::istringstream(value) >> v;
    } else if (targetType == typeid(unsigned int)) {
        unsigned int & v = *reinterpret_cast<unsigned int *>(target);
        std::istringstream(value) >> v;
    } else if (targetType == typeid(long)) {
        long & v = *reinterpret_cast<long *>(target);
        std::istringstream(value) >> v;
    } else if (targetType == typeid(unsigned long)) {
        unsigned long & v = *reinterpret_cast<unsigned long *>(target);
        std::istringstream(value) >> v;
    } else if (targetType == typeid(long long)) {
        long long & v = *reinterpret_cast<long long *>(target);
        std::istringstream(value) >> v;
    } else if (targetType == typeid(unsigned long long)) {
        unsigned long long & v = *reinterpret_cast<unsigned long long *>(target);
        std::istringstream(value) >> v;
    } else if (targetType == typeid(float)) {
        float & v = *reinterpret_cast<float *>(target);
        std::istringstream(value) >> v;
    } else if (targetType == typeid(double)) {
        double & v = *reinterpret_cast<double *>(target);
        std::istringstream(value) >> v;
    } else if (targetType == typeid(std::string)) {
        *reinterpret_cast<std::string *>(target) = value;
    } else {
        return false;
    }

    return true;
}


// Type conversion for bool
template <typename Type>
BoolConverter<Type>::BoolConverter()
{
}

template <typename Type>
BoolConverter<Type>::~BoolConverter()
{
}

template <typename Type>
bool BoolConverter<Type>::convert(const Type & value, void * target, const std::type_info & targetType) const
{
    if (targetType == typeid(std::string)) {
        *reinterpret_cast<std::string *>(target) = (value ? "true" : "false");
        return true;
    } else {
        return PrimitiveTypeConverter<Type>::convert(value, target, targetType);
    }
}


// Type conversion (default empty implemention)
template <typename Type>
TypeConverter<Type>::TypeConverter()
{
}

template <typename Type>
TypeConverter<Type>::~TypeConverter()
{
}

template <typename Type>
bool TypeConverter<Type>::canConvert(const std::type_info & /*targetType*/) const
{
    return false;
}

template <typename Type>
bool TypeConverter<Type>::convert(const Type & /*value*/, void * /*target*/, const std::type_info & /*targetType*/) const
{
    return false;
}


} // namespace reflectionzeug
