
#pragma once

#include <propertyzeug/propertyzeug.h>

#include "BaseAttribute.h"
#include "LimitAttribute.h"
#include "StringAttribute.h"

#include "Color.h"
#include "FilePath.h"

namespace propertyzeug {

/* @brief
 * Dynamic Attribute class.
 * Supported Types:
 *   - bool
 *   - [unsigned] int
 *   - [unsigned] long
 *   - [unsigned] char
 *   - float
 *   - double
 *   - std::string
 *   - Color
 *   - FilePath
 */

template <typename Type>
class Attribute;
    
template <>
class Attribute<bool> : public BaseAttribute<bool>
{
public:
    Attribute(const std::string & name, const std::string & title, const bool & value)
    :   BaseAttribute<bool>(name, title, value) {};

    Attribute(const std::string & name, const std::string & title, 
              const std::function<const bool & ()> & getter,
              const std::function<void(const bool &)> & setter)
    :   BaseAttribute<bool>(name, title, getter, setter) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, const bool & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const bool &))
    :   BaseAttribute<bool>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, bool (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(bool))
    :   BaseAttribute<bool>(name, title, object, getter_pointer, setter_pointer) {};
};

template <>
class Attribute<int> : public LimitAttribute<int>
{
public:
    Attribute(const std::string & name, const std::string & title, const int & value)
    :   LimitAttribute<int>(name, title, value) {};
    
    Attribute(const std::string & name, const std::string & title,
              const std::function<const int & ()> & getter,
              const std::function<void(const int &)> & setter)
    :   LimitAttribute<int>(name, title, getter, setter) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, const int & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const int &))
    :   LimitAttribute<int>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, int (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(int))
    :   LimitAttribute<int>(name, title, object, getter_pointer, setter_pointer) {};
};

template <>
class Attribute<unsigned int> : public LimitAttribute<unsigned int>
{
public:
    Attribute(const std::string & name, const std::string & title, const unsigned int & value)
    :   LimitAttribute<unsigned int>(name, title, value) {};
    
    Attribute(const std::string & name, const std::string & title,
              const std::function<const unsigned int & ()> & getter,
              const std::function<void(const unsigned int &)> & setter)
    :   LimitAttribute<unsigned int>(name, title, getter, setter) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, const unsigned int & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned int &))
    :   LimitAttribute<unsigned int>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, unsigned int (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(unsigned int))
    :   LimitAttribute<unsigned int>(name, title, object, getter_pointer, setter_pointer) {};
};

template <>
class Attribute<long> : public LimitAttribute<long>
{
public:
    Attribute(const std::string & name, const std::string & title, const long & value)
    :   LimitAttribute<long>(name, title, value) {};
    
    Attribute(const std::string & name, const std::string & title,
              const std::function<const long & ()> & getter,
              const std::function<void(const long &)> & setter)
    :   LimitAttribute<long>(name, title, getter, setter) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, const long & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const long &))
    :   LimitAttribute<long>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, long (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(long))
    :   LimitAttribute<long>(name, title, object, getter_pointer, setter_pointer) {};
};

template <>
class Attribute<unsigned long> : public LimitAttribute<unsigned long>
{
public:
    Attribute(const std::string & name, const std::string & title, const unsigned long & value)
    :   LimitAttribute<unsigned long>(name, title, value) {};
    
    Attribute(const std::string & name, const std::string & title,
              const std::function<const unsigned long & ()> & getter,
              const std::function<void(const unsigned long &)> & setter)
    :   LimitAttribute<unsigned long>(name, title, getter, setter) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, const unsigned long & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned long &))
    :   LimitAttribute<unsigned long>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, unsigned long (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(unsigned long))
    :   LimitAttribute<unsigned long>(name, title, object, getter_pointer, setter_pointer) {};
};

template <>
class Attribute<char> : public LimitAttribute<char>
{
public:
    Attribute(const std::string & name, const std::string & title, const char & value)
    :   LimitAttribute<char>(name, title, value) {};
    
    Attribute(const std::string & name, const std::string & title,
              const std::function<const char & ()> & getter,
              const std::function<void(const char &)> & setter)
    :   LimitAttribute<char>(name, title, getter, setter) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, const char & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const char &))
    :   LimitAttribute<char>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, char (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(char))
    :   LimitAttribute<char>(name, title, object, getter_pointer, setter_pointer) {};
};

template <>
class Attribute<unsigned char> : public LimitAttribute<unsigned char>
{
public:
    Attribute(const std::string & name, const std::string & title, const unsigned char & value)
    :   LimitAttribute<unsigned char>(name, title, value) {};
    
    Attribute(const std::string & name, const std::string & title,
              const std::function<const unsigned char & ()> & getter,
              const std::function<void(const unsigned char &)> & setter)
    :   LimitAttribute<unsigned char>(name, title, getter, setter) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, const unsigned char & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned char &))
    :   LimitAttribute<unsigned char>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, unsigned char (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(unsigned char))
    :   LimitAttribute<unsigned char>(name, title, object, getter_pointer, setter_pointer) {};
};

template <>
class Attribute<float> : public LimitAttribute<float>
{
public:
    Attribute(const std::string & name, const std::string & title, const float & value)
    :   LimitAttribute<float>(name, title, value) {};
    
    Attribute(const std::string & name, const std::string & title,
              const std::function<const float & ()> & getter,
              const std::function<void(const float &)> & setter)
    :   LimitAttribute<float>(name, title, getter, setter) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, const float & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const float &))
    :   LimitAttribute<float>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, float (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(float))
    :   LimitAttribute<float>(name, title, object, getter_pointer, setter_pointer) {};
};

template <>
class Attribute<double> : public LimitAttribute<double>
{
public:
    Attribute(const std::string & name, const std::string & title, const double & value)
    :   LimitAttribute<double>(name, title, value) {};
    
    Attribute(const std::string & name, const std::string & title,
              const std::function<const double & ()> & getter,
              const std::function<void(const double &)> & setter)
    :   LimitAttribute<double>(name, title, getter, setter) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, const double & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const double &))
    :   LimitAttribute<double>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, double (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(double))
    :   LimitAttribute<double>(name, title, object, getter_pointer, setter_pointer) {};
};

template <>
class Attribute<std::string> : public StringAttribute
{
public:
    Attribute(const std::string & name, const std::string & title, const std::string & value)
    :   StringAttribute(name, title, value) {};
    
    Attribute(const std::string & name, const std::string & title,
                  const std::function<const std::string & ()> & getter,
                  const std::function<void(const std::string &)> & setter)
    :   StringAttribute(name, title, getter, setter) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
                  Object & object, const std::string & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const std::string &))
    :   StringAttribute(name, title, object, getter_pointer, setter_pointer) {};   
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
                  Object & object, std::string (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(std::string))
    :   StringAttribute(name, title, object, getter_pointer, setter_pointer) {};   
};
    
template <>
class Attribute<Color> : public BaseAttribute<Color>
{
public:
    Attribute(const std::string & name, const std::string & title, const Color & value)
    :   BaseAttribute<Color>(name, title, value) {};
    
    Attribute(const std::string & name, const std::string & title,
              const std::function<const Color & ()> & getter,
              const std::function<void(const Color &)> & setter)
    :   BaseAttribute<Color>(name, title, getter, setter) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, const Color & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const Color &))
    :   BaseAttribute<Color>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, Color (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(Color))
    :   BaseAttribute<Color>(name, title, object, getter_pointer, setter_pointer) {};
};

template <>
class Attribute<FilePath> : public BaseAttribute<FilePath>
{
public:
    Attribute(const std::string & name, const std::string & title, const FilePath & value)
    :   BaseAttribute<FilePath>(name, title, value) {};
    
    Attribute(const std::string & name, const std::string & title,
              const std::function<const FilePath & ()> & getter,
              const std::function<void(const FilePath &)> & setter)
    :   BaseAttribute<FilePath>(name, title, getter, setter) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, const FilePath & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const FilePath &))
    :   BaseAttribute<FilePath>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Attribute(const std::string & name, const std::string & title,
              Object & object, FilePath (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(FilePath))
    :   BaseAttribute<FilePath>(name, title, object, getter_pointer, setter_pointer) {};
};

} // namespace