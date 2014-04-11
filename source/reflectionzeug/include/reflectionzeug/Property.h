
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
#include <reflectionzeug/FilePath.h>

#include <reflectionzeug/specialization_helpers.h>
#include <reflectionzeug/util.h>

namespace reflectionzeug
{

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
class Property<Type, typename EnableIf<isBoolArray<Type>::value>::type> : public ArrayProperty<Type>
{
public:
    Property(const std::string & name, const Type & value) : 
       ValuePropertyInterface(name),
       ArrayProperty<Type>(value) {}
       
   template <typename... Args>
   Property(const std::string & name, Args&&... args) : 
       ValuePropertyInterface(name),
       ArrayProperty<Type>(std::forward<Args>(args)...) {}

protected:
   virtual std::string elementRegex() const { return "true|false"; }
   virtual std::string elementToString(const bool & element) const { return element ? "true" : "false"; }
   virtual bool elementFromString(const std::string & string) const { return string == "true"; }

};

template <typename Type>
class Property<Type, typename EnableIf<isIntArray<Type>::value>::type> : public ArrayProperty<Type>
{
public:
    Property(const std::string & name, const Type & value) : 
       ValuePropertyInterface(name),
       ArrayProperty<Type>(value) {}

    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        ArrayProperty<Type>(std::forward<Args>(args)...) {}

protected:
    virtual std::string elementRegex() const { return "(-|\\+)?\\d+"; }
    virtual std::string elementToString(const int & element) const { return util::toString(element); }
    virtual int elementFromString(const std::string & string) const { return util::fromString<int>(string); }

};

template <typename Type>
class Property<Type, typename EnableIf<isDoubleArray<Type>::value>::type> : public ArrayProperty<Type>
{
public:
   Property(const std::string & name, const Type & value) : 
       ValuePropertyInterface(name),
       ArrayProperty<Type>(value) {}

   template <typename... Args>
   Property(const std::string & name, Args&&... args) : 
       ValuePropertyInterface(name),
       ArrayProperty<Type>(std::forward<Args>(args)...) {}

protected:
   virtual std::string elementRegex() const { return "(-|\\+)?\\d+\\.?\\d*"; }
   virtual std::string elementToString(const double & element) const { return util::toString(element); }
   virtual double elementFromString(const std::string & string) const { return util::fromString<double>(string); }

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

template <typename Type>
class Property<Type, typename EnableIf<std::is_class<Type>::value, Neg<isArray<Type>>::value>::type> : public ClassProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        ClassProperty<Type>(std::forward<Args>(args)...) {}

};

} // namespace reflectionzeug
