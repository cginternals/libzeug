
#pragma once

#include <propertyzeug/propertyzeug.h>

#include "BaseProperty.h"
#include "LimitProperty.h"
#include "StringProperty.h"

#include "Color.h"
#include "FilePath.h"

#include "AbstractPropertyVisitor.h"

namespace propertyzeug {

/** @brief
 * Part of the property hierarchy
 * Has different implementation based on its template Type.
 * Only this class should be instantiated!
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
class Property;
    
template <>
class Property<bool> : public BaseProperty<bool>
{
public:
    Property(const std::string & name, const std::string & title, const bool & value)
    :   BaseProperty<bool>(name, title, value) {};

    Property(const std::string & name, const std::string & title, 
              const std::function<const bool & ()> & getter,
              const std::function<void(const bool &)> & setter)
    :   BaseProperty<bool>(name, title, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, const bool & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const bool &))
    :   BaseProperty<bool>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, bool (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const bool &))
    :   BaseProperty<bool>(name, title, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<int> : public LimitProperty<int>
{
public:
    Property(const std::string & name, const std::string & title, const int & value)
    :   LimitProperty<int>(name, title, value) {};
    
    Property(const std::string & name, const std::string & title,
              const std::function<const int & ()> & getter,
              const std::function<void(const int &)> & setter)
    :   LimitProperty<int>(name, title, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, const int & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const int &))
    :   LimitProperty<int>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, int (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const int &))
    :   LimitProperty<int>(name, title, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<unsigned int> : public LimitProperty<unsigned int>
{
public:
    Property(const std::string & name, const std::string & title, const unsigned int & value)
    :   LimitProperty<unsigned int>(name, title, value) {};
    
    Property(const std::string & name, const std::string & title,
              const std::function<const unsigned int & ()> & getter,
              const std::function<void(const unsigned int &)> & setter)
    :   LimitProperty<unsigned int>(name, title, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, const unsigned int & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned int &))
    :   LimitProperty<unsigned int>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, unsigned int (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned int &))
    :   LimitProperty<unsigned int>(name, title, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<long> : public LimitProperty<long>
{
public:
    Property(const std::string & name, const std::string & title, const long & value)
    :   LimitProperty<long>(name, title, value) {};
    
    Property(const std::string & name, const std::string & title,
              const std::function<const long & ()> & getter,
              const std::function<void(const long &)> & setter)
    :   LimitProperty<long>(name, title, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, const long & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const long &))
    :   LimitProperty<long>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, long (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const long &))
    :   LimitProperty<long>(name, title, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<unsigned long> : public LimitProperty<unsigned long>
{
public:
    Property(const std::string & name, const std::string & title, const unsigned long & value)
    :   LimitProperty<unsigned long>(name, title, value) {};
    
    Property(const std::string & name, const std::string & title,
              const std::function<const unsigned long & ()> & getter,
              const std::function<void(const unsigned long &)> & setter)
    :   LimitProperty<unsigned long>(name, title, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, const unsigned long & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned long &))
    :   LimitProperty<unsigned long>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, unsigned long (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned long &))
    :   LimitProperty<unsigned long>(name, title, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<char> : public LimitProperty<char>
{
public:
    Property(const std::string & name, const std::string & title, const char & value)
    :   LimitProperty<char>(name, title, value) {};
    
    Property(const std::string & name, const std::string & title,
              const std::function<const char & ()> & getter,
              const std::function<void(const char &)> & setter)
    :   LimitProperty<char>(name, title, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, const char & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const char &))
    :   LimitProperty<char>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, char (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const char &))
    :   LimitProperty<char>(name, title, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<unsigned char> : public LimitProperty<unsigned char>
{
public:
    Property(const std::string & name, const std::string & title, const unsigned char & value)
    :   LimitProperty<unsigned char>(name, title, value) {};
    
    Property(const std::string & name, const std::string & title,
              const std::function<const unsigned char & ()> & getter,
              const std::function<void(const unsigned char &)> & setter)
    :   LimitProperty<unsigned char>(name, title, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, const unsigned char & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned char &))
    :   LimitProperty<unsigned char>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, unsigned char (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned char &))
    :   LimitProperty<unsigned char>(name, title, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<float> : public LimitProperty<float>
{
public:
    Property(const std::string & name, const std::string & title, const float & value)
    :   LimitProperty<float>(name, title, value) {};
    
    Property(const std::string & name, const std::string & title,
              const std::function<const float & ()> & getter,
              const std::function<void(const float &)> & setter)
    :   LimitProperty<float>(name, title, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, const float & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const float &))
    :   LimitProperty<float>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, float (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const float &))
    :   LimitProperty<float>(name, title, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<double> : public LimitProperty<double>
{
public:
    Property(const std::string & name, const std::string & title, const double & value)
    :   LimitProperty<double>(name, title, value) {};
    
    Property(const std::string & name, const std::string & title,
              const std::function<const double & ()> & getter,
              const std::function<void(const double &)> & setter)
    :   LimitProperty<double>(name, title, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, const double & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const double &))
    :   LimitProperty<double>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, double (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const double &))
    :   LimitProperty<double>(name, title, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<std::string> : public StringProperty
{
public:
    Property(const std::string & name, const std::string & title, const std::string & value)
    :   StringProperty(name, title, value) {};
    
    Property(const std::string & name, const std::string & title,
                  const std::function<const std::string & ()> & getter,
                  const std::function<void(const std::string &)> & setter)
    :   StringProperty(name, title, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
                  Object & object, const std::string & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const std::string &))
    :   StringProperty(name, title, object, getter_pointer, setter_pointer) {};   
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
                  Object & object, std::string (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const std::string &))
    :   StringProperty(name, title, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};
    
template <>
class Property<Color> : public BaseProperty<Color>
{
public:
    Property(const std::string & name, const std::string & title, const Color & value)
    :   BaseProperty<Color>(name, title, value) {};
    
    Property(const std::string & name, const std::string & title,
              const std::function<const Color & ()> & getter,
              const std::function<void(const Color &)> & setter)
    :   BaseProperty<Color>(name, title, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, const Color & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const Color &))
    :   BaseProperty<Color>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, Color (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const Color &))
    :   BaseProperty<Color>(name, title, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<FilePath> : public BaseProperty<FilePath>
{
public:
    Property(const std::string & name, const std::string & title, const FilePath & value)
    :   BaseProperty<FilePath>(name, title, value) {};
    
    Property(const std::string & name, const std::string & title,
              const std::function<const FilePath & ()> & getter,
              const std::function<void(const FilePath &)> & setter)
    :   BaseProperty<FilePath>(name, title, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, const FilePath & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const FilePath &))
    :   BaseProperty<FilePath>(name, title, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name, const std::string & title,
              Object & object, FilePath (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const FilePath &))
    :   BaseProperty<FilePath>(name, title, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

} // namespace