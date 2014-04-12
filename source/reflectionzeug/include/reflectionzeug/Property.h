
#pragma once

#include <array>

#include <reflectionzeug/property_declaration.h>

#include <reflectionzeug/ValueProperty.h>
#include <reflectionzeug/ClassProperty.h>
#include <reflectionzeug/NumberProperty.h>
#include <reflectionzeug/UnsignedIntegralProperty.h>
#include <reflectionzeug/SignedIntegralProperty.h>
#include <reflectionzeug/FloatingPointProperty.h>
#include <reflectionzeug/StringProperty.h>
#include <reflectionzeug/ArrayProperty.h>
#include <reflectionzeug/FilePathProperty.h>
#include <reflectionzeug/EnumProperty.h>

#include <reflectionzeug/Color.h>

#include <reflectionzeug/specialization_helpers.h>
#include <reflectionzeug/util.h>

namespace reflectionzeug
{

template <typename Type, typename>
class Property : public ClassProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        ClassProperty<Type>(std::forward<Args>(args)...) {}

};

template <>
class Property<bool> : public ValueProperty<bool>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        ValueProperty<bool>(std::forward<Args>(args)...) {}

    virtual std::string toString() const { return this->value() ? "true" : "false"; }

    virtual bool fromString(const std::string & string)
    {
        if (!util::matchesRegex(string, "(true|false)"))
            return false;

        this->setValue(string == "true");

        return true;
    }

    void toggleValue() { setValue(!value()); }

};

template <>
class Property<std::string> : public StringProperty
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        StringProperty(std::forward<Args>(args)...) {}

};

template <>
class Property<FilePath> : public FilePathProperty
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        FilePathProperty(std::forward<Args>(args)...) {}

};

template <typename Type>
class Property<Type, typename EnableIf<isUnsignedIntegral<Type>::value>::type> : public UnsignedIntegralProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        UnsignedIntegralProperty<Type>(std::forward<Args>(args)...) {}

};

template <typename Type>
class Property<Type, typename EnableIf<isSignedIntegral<Type>::value>::type> : public SignedIntegralProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        SignedIntegralProperty<Type>(std::forward<Args>(args)...) {}

};

template <typename Type>
class Property<Type, typename EnableIf<isFloatingPoint<Type>::value>::type> : public FloatingPointProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name), 
        FloatingPointProperty<Type>(std::forward<Args>(args)...) {}

};
    
template <typename Type>
    class Property<Type, typename EnableIf<isArray<Type>::value>::type> : public ArrayProperty<typename Type::value_type, std::tuple_size<Type>::value>
{
public:
    Property(const std::string & name, const Type & array) :
        ArrayProperty<typename Type::value_type, std::tuple_size<Type>::value>(name, array) {}
    
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ArrayProperty<typename Type::value_type, std::tuple_size<Type>::value>(name, std::forward<Args>(args)...) {}
    
};

template <typename Type>
class Property<Type, typename EnableIf<std::is_enum<Type>::value>::type> : public EnumProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        EnumProperty<Type>(std::forward<Args>(args)...) {}
    
};

} // namespace reflectionzeug
