
#pragma once

#include <propertyzeug/propertyzeug.h>

#include "ValueProperty.h"
#include "NumberProperty.h"
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
class Property<bool> : public ValueProperty<bool>
{
public:
    Property(const std::string & name, const bool & value)
    :   ValueProperty<bool>(name, value) {};

    Property(const std::string & name, 
              const std::function<const bool & ()> & getter,
              const std::function<void(const bool &)> & setter)
    :   ValueProperty<bool>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const bool & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const bool &))
    :   ValueProperty<bool>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, bool (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const bool &))
    :   ValueProperty<bool>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
    virtual std::string valueAsString() const { return this->value() ? "true" : "false"; };
};

template <>
class Property<int> : public NumberProperty<int>
{
public:
    Property(const std::string & name, const int & value)
    :   NumberProperty<int>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const int & ()> & getter,
              const std::function<void(const int &)> & setter)
    :   NumberProperty<int>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const int & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const int &))
    :   NumberProperty<int>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, int (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const int &))
    :   NumberProperty<int>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<unsigned int> : public NumberProperty<unsigned int>
{
public:
    Property(const std::string & name, const unsigned int & value)
    :   NumberProperty<unsigned int>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const unsigned int & ()> & getter,
              const std::function<void(const unsigned int &)> & setter)
    :   NumberProperty<unsigned int>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const unsigned int & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned int &))
    :   NumberProperty<unsigned int>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, unsigned int (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned int &))
    :   NumberProperty<unsigned int>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<long> : public NumberProperty<long>
{
public:
    Property(const std::string & name, const long & value)
    :   NumberProperty<long>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const long & ()> & getter,
              const std::function<void(const long &)> & setter)
    :   NumberProperty<long>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const long & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const long &))
    :   NumberProperty<long>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, long (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const long &))
    :   NumberProperty<long>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<unsigned long> : public NumberProperty<unsigned long>
{
public:
    Property(const std::string & name, const unsigned long & value)
    :   NumberProperty<unsigned long>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const unsigned long & ()> & getter,
              const std::function<void(const unsigned long &)> & setter)
    :   NumberProperty<unsigned long>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const unsigned long & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned long &))
    :   NumberProperty<unsigned long>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, unsigned long (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned long &))
    :   NumberProperty<unsigned long>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<char> : public NumberProperty<char>
{
public:
    Property(const std::string & name, const char & value)
    :   NumberProperty<char>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const char & ()> & getter,
              const std::function<void(const char &)> & setter)
    :   NumberProperty<char>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const char & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const char &))
    :   NumberProperty<char>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, char (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const char &))
    :   NumberProperty<char>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<unsigned char> : public NumberProperty<unsigned char>
{
public:
    Property(const std::string & name, const unsigned char & value)
    :   NumberProperty<unsigned char>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const unsigned char & ()> & getter,
              const std::function<void(const unsigned char &)> & setter)
    :   NumberProperty<unsigned char>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const unsigned char & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned char &))
    :   NumberProperty<unsigned char>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, unsigned char (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const unsigned char &))
    :   NumberProperty<unsigned char>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<float> : public NumberProperty<float>
{
public:
    Property(const std::string & name, const float & value)
    :   NumberProperty<float>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const float & ()> & getter,
              const std::function<void(const float &)> & setter)
    :   NumberProperty<float>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const float & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const float &))
    :   NumberProperty<float>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, float (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const float &))
    :   NumberProperty<float>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
};

template <>
class Property<double> : public NumberProperty<double>
{
public:
    Property(const std::string & name, const double & value)
    :   NumberProperty<double>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const double & ()> & getter,
              const std::function<void(const double &)> & setter)
    :   NumberProperty<double>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const double & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const double &))
    :   NumberProperty<double>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, double (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const double &))
    :   NumberProperty<double>(name, object, getter_pointer, setter_pointer) {};

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
class Property<Color> : public ValueProperty<Color>
{
public:
    Property(const std::string & name, const Color & value)
    :   ValueProperty<Color>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const Color & ()> & getter,
              const std::function<void(const Color &)> & setter)
    :   ValueProperty<Color>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const Color & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const Color &))
    :   ValueProperty<Color>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, Color (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const Color &))
    :   ValueProperty<Color>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
    
    virtual std::string valueAsString() const
    {
        std::stringstream stream;
        stream << "(";
        stream << this->value().red() << ",";
        stream << this->value().green() << ",";
        stream << this->value().blue() << ",";
        stream << this->value().alpha();
        stream << ")";
        return stream.str();
    }
};

template <>
class Property<FilePath> : public ValueProperty<FilePath>
{
public:
    Property(const std::string & name, const FilePath & value)
    :   ValueProperty<FilePath>(name, value) {};
    
    Property(const std::string & name,
              const std::function<const FilePath & ()> & getter,
              const std::function<void(const FilePath &)> & setter)
    :   ValueProperty<FilePath>(name, getter, setter) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, const FilePath & (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const FilePath &))
    :   ValueProperty<FilePath>(name, object, getter_pointer, setter_pointer) {};
    
    template <class Object>
    Property(const std::string & name,
              Object & object, FilePath (Object::*getter_pointer)() const,
              void (Object::*setter_pointer)(const FilePath &))
    :   ValueProperty<FilePath>(name, object, getter_pointer, setter_pointer) {};

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); };
    virtual std::string valueAsString() const { return this->value().string(); };
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
    
    virtual std::string valueAsString() const
    {
        std::stringstream stream;
        stream << "(";
        for(auto e = this->value().begin(); e < --this->value().end(); e++) {
            stream << (*e ? "true" : "false") << ",";
        }
        stream << (this->value().back() ? "true" : "false");
        stream << ")";
        
        return stream.str();
    }
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
