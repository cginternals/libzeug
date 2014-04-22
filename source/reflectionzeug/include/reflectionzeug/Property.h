
#pragma once

#include <array>

#include <reflectionzeug/property_declaration.h>

#include <reflectionzeug/BoolProperty.h>
#include <reflectionzeug/ClassProperty.h>
#include <reflectionzeug/FilePathProperty.h>
#include <reflectionzeug/UnsignedIntegralProperty.h>
#include <reflectionzeug/SignedIntegralProperty.h>
#include <reflectionzeug/FloatingPointProperty.h>
#include <reflectionzeug/StringProperty.h>
#include <reflectionzeug/ArrayProperty.h>
#include <reflectionzeug/EnumProperty.h>

#include <reflectionzeug/Color.h>

#include <reflectionzeug/specialization_helpers.h>

namespace reflectionzeug
{

template <typename Type, typename>
class Property : public ClassProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        ClassProperty<Type>(std::forward<Args>(args)...) {}

};

template <>
class Property<bool> : public BoolProperty
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        BoolProperty(std::forward<Args>(args)...) {}

};

template <>
class Property<std::string> : public StringProperty
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        StringProperty(std::forward<Args>(args)...) {}

};

template <>
class Property<FilePath> : public FilePathProperty
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        FilePathProperty(std::forward<Args>(args)...) {}

};

template <typename Type>
class Property<Type, EnableIf<isUnsignedIntegral<Type>>> : public UnsignedIntegralProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        UnsignedIntegralProperty<Type>(std::forward<Args>(args)...) {}

};

template <typename Type>
class Property<Type, EnableIf<isSignedIntegral<Type>>> : public SignedIntegralProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        SignedIntegralProperty<Type>(std::forward<Args>(args)...) {}

};

template <typename Type>
class Property<Type, EnableIf<isFloatingPoint<Type>>> : public FloatingPointProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name), 
        FloatingPointProperty<Type>(std::forward<Args>(args)...) {}

};
    
template <typename Type>
class Property<Type, EnableIf<isArray<Type>>> : public ArrayProperty<typename Type::value_type, std::tuple_size<Type>::value>
{
public:
    Property(const std::string & name, const Type & array) :
        AbstractProperty(name),
        ArrayProperty<typename Type::value_type, std::tuple_size<Type>::value>(array) {}
    
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        ArrayProperty<typename Type::value_type, std::tuple_size<Type>::value>(std::forward<Args>(args)...) {}
    
};

template <typename Type>
class Property<Type, EnableIf<std::is_enum<Type>>> : public EnumProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        EnumProperty<Type>(std::forward<Args>(args)...) {}
    
};

} // namespace reflectionzeug
