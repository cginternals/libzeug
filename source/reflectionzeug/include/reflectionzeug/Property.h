
#pragma once

#include <set>

#include <reflectionzeug/reflectionzeug.h>

#include <reflectionzeug/ValuePropertyTemplate.h>
#include <reflectionzeug/NumberProperty.h>
#include <reflectionzeug/StringProperty.h>
#include <reflectionzeug/VectorProperty.h>
#include <reflectionzeug/FilePathProperty.h>

#include <reflectionzeug/Color.h>
#include <reflectionzeug/FilePath.h>

#include <reflectionzeug/Utility.h>


namespace reflectionzeug
{

/** \brief Part of the property hierarchy, that has different implementation based on its template Type.

    Only this class should be instantiated!
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
class Property<bool> : public ValuePropertyTemplate<bool>
{
public:
    Property(const std::string & name, const bool & value)
    :   ValuePropertyTemplate<bool>(name, value) {}

    Property(const std::string & name,
             const std::function<bool ()> & getter,
             const std::function<void(const bool &)> & setter)
    :   ValuePropertyTemplate<bool>(name, getter, setter) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, const bool & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const bool &))
    :   ValuePropertyTemplate<bool>(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, bool (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const bool &))
    :   ValuePropertyTemplate<bool>(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, bool (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(bool))
    :   ValuePropertyTemplate<bool>(name, object, getter_pointer, setter_pointer) {}

    virtual std::string toString() const { return this->value() ? "true" : "false"; }

    void toggleValue() { setValue(!value()); }

};

template <>
class Property<int> : public NumberProperty<int>
{
public:
    Property(const std::string & name, const int & value)
    :   NumberProperty<int>(name, value) {}

    Property(const std::string & name,
             const std::function<int ()> & getter,
             const std::function<void(const int &)> & setter)
    :   NumberProperty<int>(name, getter, setter) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, const int & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const int &))
    :   NumberProperty<int>(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, int (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const int &))
    :   NumberProperty<int>(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, int (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(int))
    :   NumberProperty<int>(name, object, getter_pointer, setter_pointer) {}

protected:
    virtual std::string matchRegex() { return "(-|\\+)?\\d+"; }

};

template <>
class Property<double> : public NumberProperty<double>
{
public:
    Property(const std::string & name, const double & value)
    :   NumberProperty<double>(name, value)
    ,   m_precision(0)
    {}

    Property(const std::string & name,
             const std::function<double ()> & getter,
             const std::function<void(const double &)> & setter)
    :   NumberProperty<double>(name, getter, setter)
    ,   m_precision(0)
    {}

    template <class Object>
    Property(const std::string & name,
             Object & object, const double & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const double &))
    :   NumberProperty<double>(name, object, getter_pointer, setter_pointer)
    ,   m_precision(0)
    {}

    template <class Object>
    Property(const std::string & name,
             Object & object, double (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const double &))
    :   NumberProperty<double>(name, object, getter_pointer, setter_pointer)
    ,   m_precision(0)
    {}

    template <class Object>
    Property(const std::string & name,
             Object & object, double (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(double))
    :   NumberProperty<double>(name, object, getter_pointer, setter_pointer)
    ,   m_precision(0)
    {}

    virtual std::string matchRegex() { return "(-|\\+)?\\d+\\.?\\d*"; }


    unsigned int precision() const { return m_precision; }
    void setPrecision(unsigned int precision) { m_precision = precision; }
    bool hasPrecision() const { return m_precision != 0; }

protected:
    unsigned int m_precision;

};

template <>
class Property<std::string> : public StringProperty
{
public:
    Property(const std::string & name, const std::string & value)
    :   StringProperty(name, value) {}

    Property(const std::string & name,
             const std::function<std::string ()> & getter,
             const std::function<void(const std::string &)> & setter)
    :   StringProperty(name, getter, setter) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, const std::string & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::string &))
    :   StringProperty(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, std::string (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::string &))
    :   StringProperty(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, std::string (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(std::string))
    :   StringProperty(name, object, getter_pointer, setter_pointer) {}

};

template <>
class Property<Color> : public ClassProperty<Color>
{
public:
    Property(const std::string & name, const Color & value)
    :   ClassProperty<Color>(name, value) {}

    Property(const std::string & name,
             const std::function<Color ()> & getter,
             const std::function<void(const Color &)> & setter)
    :   ClassProperty<Color>(name, getter, setter) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, const Color & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const Color &))
    :   ClassProperty<Color>(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, Color (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const Color &))
    :   ClassProperty<Color>(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, Color (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(Color))
    :   ClassProperty<Color>(name, object, getter_pointer, setter_pointer) {}

};

template <>
class Property<FilePath> : public FilePathProperty
{
public:
    Property(const std::string & name, const FilePath & value)
    :   FilePathProperty(name, value) {}

    Property(const std::string & name,
             const std::function<FilePath ()> & getter,
             const std::function<void(const FilePath &)> & setter)
    :   FilePathProperty(name, getter, setter) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, const FilePath & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const FilePath &))
    :   FilePathProperty(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, FilePath (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const FilePath &))
    :   FilePathProperty(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, FilePath (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(FilePath))
    :   FilePathProperty(name, object, getter_pointer, setter_pointer) {}

};

template <>
class Property<std::vector<bool>> : public VectorProperty<bool>
{
public:
    Property(const std::string & name, const std::vector<bool> & value)
    :   VectorProperty<bool>(name, value) {}

    Property(const std::string & name,
             const std::function<std::vector<bool> ()> & getter,
             const std::function<void(const std::vector<bool> &)> & setter)
    :   VectorProperty<bool>(name, getter, setter) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, const std::vector<bool> & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::vector<bool> &))
    :   VectorProperty<bool>(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, std::vector<bool> (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::vector<bool> &))
    :   VectorProperty<bool>(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, std::vector<bool> (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(std::vector<bool>))
    :   VectorProperty<bool>(name, object, getter_pointer, setter_pointer) {}

protected:
    virtual std::string elementRegex() const { return "true|false"; }
    virtual std::string elementToString(const bool & element) const { return element ? "true" : "false"; }
    virtual bool elementFromString(const std::string & string) const { return string == "true"; }

};

template <>
class Property<std::vector<int>> : public VectorProperty<int>
{
public:
    Property(const std::string & name, const std::vector<int> & value)
    :   VectorProperty<int>(name, value) {}

    Property(const std::string & name,
             const std::function<std::vector<int> ()> & getter,
             const std::function<void(const std::vector<int> &)> & setter)
    :   VectorProperty<int>(name, getter, setter) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, const std::vector<int> & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::vector<int> &))
    :   VectorProperty<int>(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, std::vector<int> (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::vector<int> &))
    :   VectorProperty<int>(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, std::vector<int> (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(std::vector<int>))
    :   VectorProperty<int>(name, object, getter_pointer, setter_pointer) {}

protected:
    virtual std::string elementRegex() const { return "(-|\\+)?\\d+"; }
    virtual std::string elementToString(const int & element) const { return util::toString(element); }
    virtual int elementFromString(const std::string & string) const { return util::fromString<int>(string); }

};

template <>
class Property<std::vector<double>> : public VectorProperty<double>
{
public:
    Property(const std::string & name, const std::vector<double> & value)
    :   VectorProperty<double>(name, value) {}

    Property(const std::string & name,
             const std::function<std::vector<double> ()> & getter,
             const std::function<void(const std::vector<double> &)> & setter)
    :   VectorProperty<double>(name, getter, setter) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, const std::vector<double> & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::vector<double> &))
    :   VectorProperty<double>(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, std::vector<double> (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::vector<double> &))
    :   VectorProperty<double>(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, std::vector<double> (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(std::vector<double>))
    :   VectorProperty<double>(name, object, getter_pointer, setter_pointer) {}

protected:
    virtual std::string elementRegex() const { return "(-|\\+)?\\d+\\.?\\d*"; }
    virtual std::string elementToString(const double & element) const { return util::toString(element); }
    virtual double elementFromString(const std::string & string) const { return util::fromString<double>(string); }

};

// TODO: Who uses this?
// template <>
// class Property<std::set<int>> : public ValuePropertyTemplate<std::set<int>>
// {
// public:
//     Property(const std::string & name, const std::set<int> & value)
//     :   ValuePropertyTemplate<std::set<int>>(name, value) {}

//     Property(const std::string & name,
//              const std::function<std::set<int> ()> & getter,
//              const std::function<void(const std::set<int> &)> & setter)
//     :   ValuePropertyTemplate<std::set<int>>(name, getter, setter) {}

//     template <class Object>
//     Property(const std::string & name,
//              Object & object, const std::set<int> & (Object::*getter_pointer)() const,
//              void (Object::*setter_pointer)(const std::set<int> &))
//     :   ValuePropertyTemplate<std::set<int>>(name, object, getter_pointer, setter_pointer) {}

//     template <class Object>
//     Property(const std::string & name,
//              Object & object, std::set<int> (Object::*getter_pointer)() const,
//              void (Object::*setter_pointer)(const std::set<int> &))
//     :   ValuePropertyTemplate<std::set<int>>(name, object, getter_pointer, setter_pointer) {}

//     template <class Object>
//     Property(const std::string & name,
//              Object & object, std::set<int> (Object::*getter_pointer)() const,
//              void (Object::*setter_pointer)(std::set<int>))
//     :   ValuePropertyTemplate<std::set<int>>(name, object, getter_pointer, setter_pointer) {}

//     virtual std::string toString() const { return "(" + join(this->value(), ", ") + ")"; }
// };

} // namespace reflectionzeug
