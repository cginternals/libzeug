
#pragma once

#include <set>
#include <typeinfo>

#include <reflectionzeug/reflectionzeug.h>

#include <reflectionzeug/ValueProperty.h>
#include <reflectionzeug/NumberProperty.h>
#include <reflectionzeug/StringProperty.h>
#include <reflectionzeug/VectorProperty.h>
#include <reflectionzeug/FilePathProperty.h>

#include <reflectionzeug/Color.h>
#include <reflectionzeug/FilePath.h>

#include <reflectionzeug/util.h>


namespace reflectionzeug
{

/** \brief Part of the property hierarchy, that has different implementation based on its template Type.

    Only this class may be instantiated!
    Supported Types:
      - bool
      - int
      - double
      - std::string
      - Color
      - FilePath
      - std::vector<bool>
      - std::vector<int>
      - std::vector<double>
      - std::set<int>
*/
template <typename Type>
class Property;

template <>
class Property<bool> : public ValueProperty<bool>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        ValueProperty<bool>(name, std::forward<Args>(args)...) {}

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
class Property<int> : public NumberProperty<int>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        NumberProperty<int>(name, std::forward<Args>(args)...) {}

protected:
    virtual std::string matchRegex() { return "(-|\\+)?\\d+"; }

};

template <>
class Property<double> : public NumberProperty<double>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name), 
        NumberProperty<double>(name, std::forward<Args>(args)...),
        m_precision(0) {}

    unsigned int precision() const { return m_precision; }
    void setPrecision(unsigned int precision) { m_precision = precision; }
    bool hasPrecision() const { return m_precision != 0; }

protected:
    virtual std::string matchRegex() { return "(-|\\+)?\\d+\\.?\\d*"; }

protected:
    unsigned int m_precision;

};

template <>
class Property<std::string> : public StringProperty
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        StringProperty(name, std::forward<Args>(args)...) {}

};

template <>
class Property<Color> : public ClassProperty<Color>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        ClassProperty<Color>(name, std::forward<Args>(args)...) {}

};

template <>
class Property<FilePath> : public FilePathProperty
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        FilePathProperty(name, std::forward<Args>(args)...) {}

};

template <>
class Property<std::vector<bool>> : public VectorProperty<bool>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        VectorProperty<bool>(name, std::forward<Args>(args)...) {}

protected:
    virtual std::string elementRegex() const { return "true|false"; }
    virtual std::string elementToString(const bool & element) const { return element ? "true" : "false"; }
    virtual bool elementFromString(const std::string & string) const { return string == "true"; }

};

template <>
class Property<std::vector<int>> : public VectorProperty<int>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        VectorProperty<int>(name, std::forward<Args>(args)...) {}

protected:
    virtual std::string elementRegex() const { return "(-|\\+)?\\d+"; }
    virtual std::string elementToString(const int & element) const { return util::toString(element); }
    virtual int elementFromString(const std::string & string) const { return util::fromString<int>(string); }

};

template <>
class Property<std::vector<double>> : public VectorProperty<double>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        VectorProperty<double>(name, std::forward<Args>(args)...) {}

protected:
    virtual std::string elementRegex() const { return "(-|\\+)?\\d+\\.?\\d*"; }
    virtual std::string elementToString(const double & element) const { return util::toString(element); }
    virtual double elementFromString(const std::string & string) const { return util::fromString<double>(string); }

};

template <typename Type>
class Property : public ClassProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        ClassProperty<Type>(name, std::forward<Args>(args)...) {}

};

template <typename Type>
struct type
{
    static const int value;
};
    
template <typename Type>
const int type<Type>::value = typeid(Type).hash_code();

// TODO: Who uses this?
// template <>
// class Property<std::set<int>> : public ValueProperty<std::set<int>>
// {
// public:
//     Property(const std::string & name, const std::set<int> & value)
//     :   ValueProperty<std::set<int>>(name, value) {}

//     Property(const std::string & name,
//              const std::function<std::set<int> ()> & getter,
//              const std::function<void(const std::set<int> &)> & setter)
//     :   ValueProperty<std::set<int>>(name, getter, setter) {}

//     template <class Object>
//     Property(const std::string & name,
//              Object & object, const std::set<int> & (Object::*getter_pointer)() const,
//              void (Object::*setter_pointer)(const std::set<int> &))
//     :   ValueProperty<std::set<int>>(name, object, getter_pointer, setter_pointer) {}

//     template <class Object>
//     Property(const std::string & name,
//              Object & object, std::set<int> (Object::*getter_pointer)() const,
//              void (Object::*setter_pointer)(const std::set<int> &))
//     :   ValueProperty<std::set<int>>(name, object, getter_pointer, setter_pointer) {}

//     template <class Object>
//     Property(const std::string & name,
//              Object & object, std::set<int> (Object::*getter_pointer)() const,
//              void (Object::*setter_pointer)(std::set<int>))
//     :   ValueProperty<std::set<int>>(name, object, getter_pointer, setter_pointer) {}

//     virtual std::string toString() const { return "(" + join(this->value(), ", ") + ")"; }
// };

} // namespace reflectionzeug
