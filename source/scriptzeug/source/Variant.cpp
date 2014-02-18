#include <stdlib.h>
#include <sstream>
#include "scriptzeug/Variant.h"


namespace scriptzeug {


static const int           MIN_INT  = int( ~(unsigned(-1)/2) );
static const int           MAX_INT  = int(  (unsigned(-1)/2) );
static const unsigned int  MAX_UINT = unsigned(-1);


Variant Variant::Null(Variant::TypeNull);


/**
*  @brief
*    Create an empty object
*/
Variant Variant::Object()
{
    return Variant(TypeObject);
}

/**
*  @brief
*    Create an empty array
*/
Variant Variant::Array()
{
    return Variant(TypeArray);
}


/**
*  @brief
*    Constructor
*/
Variant::Variant(Type type) :
    m_type(type),
    m_string("")
{
    // Initialize value
    switch (m_type) {
        case TypeInt:     m_int    = 0;     break;
        case TypeUInt:    m_uint   = 0;     break;
        case TypeDouble:  m_double = 0.0;   break;
        case TypeBool:    m_bool   = false; break;
        default:          break;
    }
}

Variant::Variant(int value) :
    m_type(TypeInt),
    m_string("")
{
    // Initialize value
    m_int = value;
}

Variant::Variant(unsigned int value) :
    m_type(TypeUInt),
    m_string("")
{
    // Initialize value
    m_uint = value;
}

Variant::Variant(double value) :
    m_type(TypeDouble),
    m_string("")
{
    // Initialize value
    m_double = value;
}

Variant::Variant(bool value) :
    m_type(TypeBool),
    m_string("")
{
    // Initialize value
    m_bool = value;
}

Variant::Variant(const std::string &value) :
    m_type(TypeString),
    m_string(value)
{
}

Variant::Variant(const std::vector<std::string> &values) :
    m_type(TypeArray),
    m_string("")
{
    for (std::vector<std::string>::const_iterator it = values.begin(); it != values.end(); ++it) {
        std::string value = *it;
        append(value);
    }
}

Variant::Variant(const char *value) :
    m_type(TypeString),
    m_string(value)
{
}

/**
*  @brief
*    Copy constructor
*/
Variant::Variant(const Variant &rh)
{
    *this = rh;
}

/**
*  @brief
*    Destructor
*/
Variant::~Variant()
{
    m_array .clear();
    m_object.clear();
}

/**
*  @brief
*    Copy operator
*/
Variant &Variant::operator =(const Variant &rh)
{
    if (this != &Null && this != &rh) {
        // Clear old data
        clear();

        // Copy type
        m_type = rh.m_type;

        // Copy value
        switch (rh.m_type) {
            case TypeInt:       m_int    = rh.m_int;    break;
            case TypeUInt:      m_uint   = rh.m_uint;   break;
            case TypeDouble:    m_double = rh.m_double; break;
            case TypeBool:      m_bool   = rh.m_bool;   break;
            case TypeString:    m_string = rh.m_string; break;
            case TypeArray:     m_array  = rh.m_array;  break;
            case TypeObject:    m_object = rh.m_object; break;
            default:            break;
        }
    }

    // Return reference
    return *this;
}

/**
*  @brief
*    Clear all data
*/
void Variant::clear()
{
    if (this != &Null) {
        m_type   = TypeNull;
        m_uint   = 0;
        m_string = "";
        m_array .clear();
        m_object.clear();
    }
}

/**
*  @brief
*    Get type of value
*/
Variant::Type Variant::type() const
{
    return m_type;
}

/**
*  @brief
*    Check if value is empty
*/
bool Variant::empty() const
{
    return (  m_type == TypeNull ||
             (m_type == TypeObject    && m_object.empty()) ||
             (m_type == TypeArray     && m_array .empty()) );
}

/**
*  @brief
*    Convert value into integer
*/
int Variant::toInt() const
{
    switch (m_type) {
        case TypeNull:      return 0;
        case TypeInt:       return m_int;
        case TypeUInt:      return (m_uint < (unsigned int)MAX_INT) ? (int)m_uint : 0;
        case TypeDouble:    return (int)m_double;
        case TypeBool:      return (m_bool ? 1 : 0);
        case TypeString:    return atoi(m_string.c_str());
        case TypeArray:
        case TypeObject:
        default:            return 0;
    }
}

/**
*  @brief
*    Convert value into unsigned integer
*/
unsigned int Variant::toUInt() const
{
    switch (m_type) {
        case TypeNull:      return 0;
        case TypeInt:       return (m_int    >= 0) ? (unsigned int)m_int    : 0;
        case TypeUInt:      return m_uint;
        case TypeDouble:    return (m_double >= 0) ? (unsigned int)m_double : 0;
        case TypeBool:      return (m_bool ? 1 : 0);
        case TypeString:    return atoi(m_string.c_str());
        case TypeArray:
        case TypeObject:
        default:            return 0;
    }
}

/**
*  @brief
*    Convert value into double
*/
double Variant::toDouble() const
{
    switch (m_type) {
        case TypeNull:      return 0.0;
        case TypeInt:       return (double)m_int;
        case TypeUInt:      return (double)m_uint;
        case TypeDouble:    return m_double;
        case TypeBool:      return (m_bool ? 1.0 : 0.0);
        case TypeString:    return atof(m_string.c_str());
        case TypeArray:
        case TypeObject:
        default:            return 0;
    }
}

/**
*  @brief
*    Convert value into boolean
*/
bool Variant::toBool() const
{
    switch (m_type) {
        case TypeNull:      return false;
        case TypeInt:       return (m_int    != 0);
        case TypeUInt:      return (m_uint   != 0);
        case TypeDouble:    return (m_double != 0.0);
        case TypeBool:      return  m_bool;
        case TypeString:    return !m_string.empty();
        case TypeArray:
        case TypeObject:
        default:            return false;
    }
}

/**
*  @brief
*    Convert value into string
*/
std::string Variant::toString() const
{
    switch (m_type) {
        case TypeNull:      return "";
        case TypeInt:       { std::stringstream c; c << m_int;    return c.str(); }
        case TypeUInt:      { std::stringstream c; c << m_uint;   return c.str(); }
        case TypeDouble:    { std::stringstream c; c << m_double; return c.str(); }
        case TypeBool:      return (m_bool ? "true" : "false");
        case TypeString:    return m_string;
        case TypeArray:
        case TypeObject:
        default:            return toJSON();
    }
}

/**
*  @brief
*    Convert value to string list
*
*  @return
*    String list
*/
StringList Variant::toStringList() const
{
    StringList list;

    // Array
    if (m_type == TypeArray) {
        // Convert each value into a string
        for (std::vector<Variant>::const_iterator it = m_array.begin(); it != m_array.end(); ++it) {
            list.push_back((*it).toString());
        }
    }

    // Other: Convert into string and create one-element list
    else {
        list.push_back(toString());
    }

    // Return list
    return list;
}

/**
*  @brief
*    Convert value to JSON notation
*/
std::string Variant::toJSON(bool nice, const std::string &indent) const
{
    // Variant is an object
    if (m_type == TypeObject) {
        // Quick output: {} if empty
        if (empty()) return "{}";

        // Begin output
        std::string json = "{";
        if (nice) json += "\n";

        // Add all variables
        bool first = true;
        for (std::map<std::string, Variant>::const_iterator it = m_object.begin(); it != m_object.end(); ++it) {
            // Add separator (",")
            if (!first) json += nice ? ",\n" : ","; else first = false;

            // Get variable
            std::string name = it->first;
            const Variant &var = it->second;

            // Get value
            std::string value;
            if (var.type() == TypeObject || var.type() == TypeArray) {
                value = var.toJSON(nice, indent + "    ");
            } else {
                value = "\"" + var.toString() + "\"";
            }

            // Add value to JSON
            json += (nice ? (indent + "    \"" + name + "\": " + value) : ("\"" + name + "\":" + value));
        }

        // Finish JSON
        json += (nice ? "\n" + indent + "}" : "}");
        return json;
    }

    // Variant is an array
    else if (m_type == TypeArray) {
        // Quick output: [] if empty
        if (empty()) return "[]";

        // Begin output
        std::string json = "[";
        if (nice) json += "\n";

        // Add all elements
        bool first = true;
        for (std::vector<Variant>::const_iterator it = m_array.begin(); it != m_array.end(); ++it) {
            // Add separator (",")
            if (!first) json += nice ? ",\n" : ","; else first = false;

            // Get variable
            const Variant &var = *it;

            // Get value
            std::string value;
            if (var.type() == TypeObject || var.type() == TypeArray) {
                value = var.toJSON(nice, indent + "    ");
            } else {
                value = "\"" + var.toString() + "\"";
            }

            // Add value to JSON
            json += (nice ? (indent + "    " + value) : value);
        }

        // Finish JSON
        json += (nice ? "\n" + indent + "]" : "]");
        return json;
    }

    // Invalid type for JSON output
    else {
        return "";
    }
}

/**
*  @brief
*    Check if value is an object
*/
bool Variant::isObject() const
{
    return (m_type == TypeObject);
}

/**
*  @brief
*    Get list of object keys
*/
StringList Variant::keys() const
{
    StringList keys;
    for (std::map<std::string, Variant>::const_iterator it = m_object.begin(); it != m_object.end(); ++it)
        keys.push_back(it->first);
    return keys;
}

/**
*  @brief
*    Check if object contains an attribute
*/
bool Variant::contains(const std::string &name) const
{
    // Only works on objects
    if (m_type == TypeObject) {
        return (m_object.count(name) > 0);
    } else {
        return false;
    }
}

/**
*  @brief
*    Get object attribute
*/
const Variant &Variant::get(const std::string &name) const
{
    // Only works on objects
    if (m_type == TypeObject && contains(name)) {
        return m_object.at(name);
    }

    // Error, return empty value
    return Variant::Null;
}

/**
*  @brief
*    Get object attribute
*/
Variant &Variant::get(const std::string &name)
{
    // Only works on objects
    if (m_type == TypeObject && contains(name)) {
        return m_object.at(name);
    }

    // Error, return empty value
    return Variant::Null;
}

/**
*  @brief
*    Get object attribute
*/
const Variant &Variant::operator [](const std::string &name) const
{
    return get(name);
}

/**
*  @brief
*    Get object attribute
*/
Variant &Variant::operator [](const std::string &name)
{
    // Only works on objects
    if (m_type == TypeObject && this != &Null) {
        // Check if attribute is present
        if (m_object.count(name) < 1) {
            // Append empty value
            Variant v;
            set(name, v);
        }

        // Return reference to value
        return m_object[name];
    }

    // Error, invalid type
    return Null;
}

/**
*  @brief
*    Set object attribute
*/
Variant &Variant::set(const std::string &name, const Variant &value)
{
    // Only works on objects
    if (m_type == TypeObject && this != &Null) {
        // Set attribute
        m_object[name] = value;
    }

    return *this;
}

/**
*  @brief
*    Remove object attribute
*/
void Variant::remove(const std::string &name)
{
    // Only works on objects
    if (m_type == TypeObject && this != &Null) {
        // Remove attribute
        m_object.erase(name);
    }
}

/**
*  @brief
*    Check if value is an array
*/
bool Variant::isArray() const
{
    return (m_type == TypeArray);
}

/**
*  @brief
*    Get size of array
*/
unsigned int Variant::size() const
{
    // Only works on arrays
    if (m_type == TypeArray) {
        return m_array.size();
    } else {
        return 0;
    }
}

/**
*  @brief
*    Get array element
*/
const Variant &Variant::get(unsigned int index) const
{
    // Only works on arrays
    if (m_type == TypeArray) {
        // Check if element exists, otherwise return empty value
        if (index < m_array.size())
            // Return a reference to the actual data, no copy
            return m_array[index];
    }

    // Error, return empty value
    return Variant::Null;
}

/**
*  @brief
*    Get array element
*/
Variant &Variant::get(unsigned int index)
{
    // Only works on arrays
    if (m_type == TypeArray) {
        // Check if element exists, otherwise return empty value
        if (index < m_array.size())
            // Return a reference to the actual data, no copy
            return m_array[index];
    }

    // Error, return empty value
    return Variant::Null;
}

/**
*  @brief
*    Get array element
*/
const Variant &Variant::operator [](unsigned int index) const
{
    return get(index);
}

/**
*  @brief
*    Get array element
*/
Variant &Variant::operator [](unsigned int index)
{
    return get(index);
}

/**
*  @brief
*    Set array element
*/
Variant &Variant::set(unsigned int index, const Variant &value)
{
    // Only works on arrays
    if (m_type == TypeArray && this != &Null) {
        // Resize container if necessary
        if (index >= m_array.size())
            m_array.resize(index+1, Variant::Null);

        // Set value
        m_array[index] = value;
    }

    return *this;
}

/**
*  @brief
*    Append element to array
*/
Variant &Variant::append(const Variant &value)
{
    // Only works on arrays
    if (m_type == TypeArray && this != &Null) {
        // Append value
        m_array.push_back(value);
    }

    return *this;
}

/**
*  @brief
*    Append new element to array
*/
Variant &Variant::append()
{
    // Only works on arrays
    if (m_type == TypeArray && this != &Null) {
        // Append empty value
        Variant v;
        append(v);

        // Return reference to new value
        return m_array[m_array.size()-1];
    }

    // Error, invalid type
    return Null;
}

/**
*  @brief
*    Remove array element
*/
void Variant::remove(unsigned int index)
{
    // Only works on arrays
    if (m_type == TypeArray && this != &Null) {
        // Remove value
        if (index < m_array.size())
            m_array.erase(m_array.begin() + index);
    }
}


} // namespace scriptzeug
