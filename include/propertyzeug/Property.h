
#pragma once

#include <propertyzeug/propertyzeug.h>

#include <propertyzeug/ValuePropertyTemplate.h>
#include <propertyzeug/NumberProperty.h>
#include <propertyzeug/StringProperty.h>
#include <propertyzeug/VectorProperty.h>
#include <propertyzeug/SetProperty.h>
#include <propertyzeug/FilePathProperty.h>

#include <propertyzeug/Color.h>
#include <propertyzeug/FilePath.h>

#include <propertyzeug/AbstractPropertyVisitor.h>


namespace zeug {

/** @brief
 * Part of the property hierarchy
 * Has different implementation based on its template Type.
 * Only this class should be instantiated!
 * Supported Types:
 *   - bool
 *   - int
 *   - double
 *   - std::string
 *   - Color
 *   - FilePath
 *   - std::vector<bool>
 *   - std::vector<int>
 *   - std::vector<double>
 *   - std::set<int>
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

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); }
    virtual std::string valueAsString() const { return this->value() ? "true" : "false"; }
    
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

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); }
};

template <>
class Property<double> : public NumberProperty<double>
{
public:
    Property(const std::string & name, const double & value)
    :   NumberProperty<double>(name, value) {}
    
    Property(const std::string & name,
             const std::function<double ()> & getter,
             const std::function<void(const double &)> & setter)
    :   NumberProperty<double>(name, getter, setter) {}
    
    template <class Object>
    Property(const std::string & name,
             Object & object, const double & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const double &))
    :   NumberProperty<double>(name, object, getter_pointer, setter_pointer) {}
    
    template <class Object>
    Property(const std::string & name,
             Object & object, double (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const double &))
    :   NumberProperty<double>(name, object, getter_pointer, setter_pointer) {}

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); }
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

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); }
};
    
template <>
class Property<Color> : public ValuePropertyTemplate<Color>
{
public:
    Property(const std::string & name, const Color & value)
    :   ValuePropertyTemplate<Color>(name, value) {}
    
    Property(const std::string & name,
             const std::function<Color ()> & getter,
             const std::function<void(const Color &)> & setter)
    :   ValuePropertyTemplate<Color>(name, getter, setter) {}
    
    template <class Object>
    Property(const std::string & name,
             Object & object, const Color & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const Color &))
    :   ValuePropertyTemplate<Color>(name, object, getter_pointer, setter_pointer) {}
    
    template <class Object>
    Property(const std::string & name,
             Object & object, Color (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const Color &))
    :   ValuePropertyTemplate<Color>(name, object, getter_pointer, setter_pointer) {}

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); }
    
    virtual std::string valueAsString() const { return this->value().asHex(); }
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

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); }
};

template <>
class Property<std::vector<bool>> : public VectorProperty<std::vector<bool>>
{
public:
    Property(const std::string & name, const std::vector<bool> & value)
    :   VectorProperty<std::vector<bool>>(name, value) {}
    
    Property(const std::string & name,
             const std::function<std::vector<bool> ()> & getter,
             const std::function<void(const std::vector<bool> &)> & setter)
    :   VectorProperty<std::vector<bool>>(name, getter, setter) {}
    
    template <class Object>
    Property(const std::string & name,
             Object & object, const std::vector<bool> & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::vector<bool> &))
    :   VectorProperty<std::vector<bool>>(name, object, getter_pointer, setter_pointer) {}
    
    template <class Object>
    Property(const std::string & name,
             Object & object, std::vector<bool> (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::vector<bool> &))
    :   VectorProperty<std::vector<bool>>(name, object, getter_pointer, setter_pointer) {}

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); }
    
    virtual std::string valueAsString() const
    {
        std::stringstream stream;
        stream << "(";
        for(auto e = this->value().begin(); e < --this->value().end(); e++) {
            stream << (*e ? "true" : "false") << ", ";
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
    :   VectorProperty<std::vector<int>>(name, value) {}
    
    Property(const std::string & name,
             const std::function<std::vector<int> ()> & getter,
             const std::function<void(const std::vector<int> &)> & setter)
    :   VectorProperty<std::vector<int>>(name, getter, setter) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, const std::vector<int> & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::vector<int> &))
    :   VectorProperty<std::vector<int>>(name, object, getter_pointer, setter_pointer) {}
    
    template <class Object>
    Property(const std::string & name,
             Object & object, std::vector<int> (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::vector<int> &))
    :   VectorProperty<std::vector<int>>(name, object, getter_pointer, setter_pointer) {}

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); }
};

template <>
class Property<std::vector<double>> : public VectorProperty<std::vector<double>>
{
public:
    Property(const std::string & name, const std::vector<double> & value)
    :   VectorProperty<std::vector<double>>(name, value) {}
    
    Property(const std::string & name,
             const std::function<std::vector<double> ()> & getter,
             const std::function<void(const std::vector<double> &)> & setter)
    :   VectorProperty<std::vector<double>>(name, getter, setter) {}
    
    template <class Object>
    Property(const std::string & name,
             Object & object, const std::vector<double> & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::vector<double> &))
    :   VectorProperty<std::vector<double>>(name, object, getter_pointer, setter_pointer) {}
    
    template <class Object>
    Property(const std::string & name,
             Object & object, std::vector<double> (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::vector<double> &))
    :   VectorProperty<std::vector<double>>(name, object, getter_pointer, setter_pointer) {}

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); }
};

template <>
class Property<std::set<int>> : public SetProperty<std::set<int>>
{
public:
    Property(const std::string & name, const std::set<int> & value)
    :   SetProperty<std::set<int>>(name, value) {}
    
    Property(const std::string & name,
             const std::function<std::set<int> ()> & getter,
             const std::function<void(const std::set<int> &)> & setter)
    :   SetProperty<std::set<int>>(name, getter, setter) {}
    
    template <class Object>
    Property(const std::string & name,
             Object & object, const std::set<int> & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::set<int> &))
    :   SetProperty<std::set<int>>(name, object, getter_pointer, setter_pointer) {}
    
    template <class Object>
    Property(const std::string & name,
             Object & object, std::set<int> (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const std::set<int> &))
    :   SetProperty<std::set<int>>(name, object, getter_pointer, setter_pointer) {}

    virtual void accept(AbstractPropertyVisitor & visitor) { visitor.visit(*this); }
};

} // namespace
