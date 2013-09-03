
#pragma once

#include <propertyzeug/propertyzeug.h>

#include "BaseProperty.h"
#include "LimitProperty.h"
#include "StringProperty.h"
#include "VectorProperty.h"

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
 *   - std::vector<bool>
 *   - std::vector<int>
 *   - std::vector<float>
 *   - std::vector<double>
 */

template <typename Type>
class Property;
    
template <>
class Property<bool> : public BaseProperty<bool>
{
public:
    Property(const std::string & name, const bool & value)
    :   BaseProperty<bool>(name, value) {};

    Property(const std::string & name, 
              const std::function<const bool & ()> & getter,
              const std::function<void(const bool &)> & setter)
    :   BaseProperty<bool>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const bool & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const bool &))
    :   BaseProperty<bool>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, bool (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const bool &))
    :   BaseProperty<bool>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<int> : public LimitProperty<int>
{
public:
    Property(const std::string & name, const int & value)
    :   LimitProperty<int>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const int & ()> & getter,
              const std::function<void(const int &)> & setter)
    :   LimitProperty<int>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const int & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const int &))
    :   LimitProperty<int>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, int (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const int &))
    :   LimitProperty<int>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<unsigned int> : public LimitProperty<unsigned int>
{
public:
    Property(const std::string & name, const unsigned int & value)
    :   LimitProperty<unsigned int>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const unsigned int & ()> & getter,
              const std::function<void(const unsigned int &)> & setter)
    :   LimitProperty<unsigned int>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const unsigned int & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned int &))
    :   LimitProperty<unsigned int>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, unsigned int (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned int &))
    :   LimitProperty<unsigned int>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<long> : public LimitProperty<long>
{
public:
    Property(const std::string & name, const long & value)
    :   LimitProperty<long>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const long & ()> & getter,
              const std::function<void(const long &)> & setter)
    :   LimitProperty<long>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const long & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const long &))
    :   LimitProperty<long>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, long (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const long &))
    :   LimitProperty<long>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<unsigned long> : public LimitProperty<unsigned long>
{
public:
    Property(const std::string & name, const unsigned long & value)
    :   LimitProperty<unsigned long>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const unsigned long & ()> & getter,
              const std::function<void(const unsigned long &)> & setter)
    :   LimitProperty<unsigned long>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const unsigned long & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned long &))
    :   LimitProperty<unsigned long>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, unsigned long (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned long &))
    :   LimitProperty<unsigned long>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<char> : public LimitProperty<char>
{
public:
    Property(const std::string & name, const char & value)
    :   LimitProperty<char>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const char & ()> & getter,
              const std::function<void(const char &)> & setter)
    :   LimitProperty<char>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const char & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const char &))
    :   LimitProperty<char>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, char (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const char &))
    :   LimitProperty<char>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<unsigned char> : public LimitProperty<unsigned char>
{
public:
    Property(const std::string & name, const unsigned char & value)
    :   LimitProperty<unsigned char>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const unsigned char & ()> & getter,
              const std::function<void(const unsigned char &)> & setter)
    :   LimitProperty<unsigned char>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const unsigned char & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned char &))
    :   LimitProperty<unsigned char>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, unsigned char (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned char &))
    :   LimitProperty<unsigned char>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<float> : public LimitProperty<float>
{
public:
    Property(const std::string & name, const float & value)
    :   LimitProperty<float>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const float & ()> & getter,
              const std::function<void(const float &)> & setter)
    :   LimitProperty<float>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const float & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const float &))
    :   LimitProperty<float>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, float (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const float &))
    :   LimitProperty<float>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<double> : public LimitProperty<double>
{
public:
    Property(const std::string & name, const double & value)
    :   LimitProperty<double>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const double & ()> & getter,
              const std::function<void(const double &)> & setter)
    :   LimitProperty<double>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const double & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const double &))
    :   LimitProperty<double>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, double (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const double &))
    :   LimitProperty<double>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<std::string> : public StringProperty
{
public:
    Property(const std::string & name, const std::string & value)
    :   StringProperty(name, value) {};
    
    Property(const std::string & name,
                  const std::function<const std::string & ()> & getter,
                  const std::function<void(const std::string &)> & setter)
    :   StringProperty(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
                  Object & object, const std::string & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const std::string &))
    :   StringProperty(name, object, getter_pointer, setter_pointer) {};   
    
    template <class Object>
    Property(const std::string & name,
                  Object & object, std::string (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const std::string &))
    :   StringProperty(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};
    
template <>
class Property<Color> : public BaseProperty<Color>
{
public:
    Property(const std::string & name, const Color & value)
    :   BaseProperty<Color>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const Color & ()> & getter,
              const std::function<void(const Color &)> & setter)
    :   BaseProperty<Color>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const Color & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const Color &))
    :   BaseProperty<Color>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, Color (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const Color &))
    :   BaseProperty<Color>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<FilePath> : public BaseProperty<FilePath>
{
public:
    Property(const std::string & name, const FilePath & value)
    :   BaseProperty<FilePath>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const FilePath & ()> & getter,
              const std::function<void(const FilePath &)> & setter)
    :   BaseProperty<FilePath>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const FilePath & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const FilePath &))
    :   BaseProperty<FilePath>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, FilePath (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const FilePath &))
    :   BaseProperty<FilePath>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<std::vector<bool>> : public VectorProperty<std::vector<bool>>
{
public:
    Property(const std::string & name, const std::vector<bool> & value)
    :   VectorProperty<std::vector<bool>>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const std::vector<bool> & ()> & getter,
              const std::function<void(const std::vector<bool> &)> & setter)
    :   VectorProperty<std::vector<bool>>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const std::vector<bool> & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const std::vector<bool> &))
    :   VectorProperty<std::vector<bool>>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, std::vector<bool> (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const std::vector<bool> &))
    :   VectorProperty<std::vector<bool>>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<std::vector<int>> : public VectorProperty<std::vector<int>>
{
public:
    Property(const std::string & name, const std::vector<int> & value)
    :   VectorProperty<std::vector<int>>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const std::vector<int> & ()> & getter,
              const std::function<void(const std::vector<int> &)> & setter)
    :   VectorProperty<std::vector<int>>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const std::vector<int> & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const std::vector<int> &))
    :   VectorProperty<std::vector<int>>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, std::vector<int> (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const std::vector<int> &))
    :   VectorProperty<std::vector<int>>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<std::vector<float>> : public VectorProperty<std::vector<float>>
{
public:
    Property(const std::string & name, const std::vector<float> & value)
    :   VectorProperty<std::vector<float>>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const std::vector<float> & ()> & getter,
              const std::function<void(const std::vector<float> &)> & setter)
    :   VectorProperty<std::vector<float>>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const std::vector<float> & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const std::vector<float> &))
    :   VectorProperty<std::vector<float>>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, std::vector<float> (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const std::vector<float> &))
    :   VectorProperty<std::vector<float>>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<std::vector<double>> : public VectorProperty<std::vector<double>>
{
public:
    Property(const std::string & name, const std::vector<double> & value)
    :   VectorProperty<std::vector<double>>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const std::vector<double> & ()> & getter,
              const std::function<void(const std::vector<double> &)> & setter)
    :   VectorProperty<std::vector<double>>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const std::vector<double> & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const std::vector<double> &))
    :   VectorProperty<std::vector<double>>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, std::vector<double> (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const std::vector<double> &))
    :   VectorProperty<std::vector<double>>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};



} // namespace
