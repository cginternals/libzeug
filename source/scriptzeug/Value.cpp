#include <stdlib.h>
#include <sstream>
#include "scriptzeug/Value.h"


namespace scriptzeug {


static const int           MIN_INT  = int( ~(unsigned(-1)/2) );
static const int           MAX_INT  = int(  (unsigned(-1)/2) );
static const unsigned int  MAX_UINT = unsigned(-1);


Value Value::Null(Value::TypeNull);


/**
*  @brief
*    Create an empty object
*/
Value Value::Object()
{
    return Value(TypeObject);
}

/**
*  @brief
*    Create an empty array
*/
Value Value::Array()
{
    return Value(TypeArray);
}


/**
*  @brief
*    Constructor
*/
Value::Value(Type type) :
    m_type(type),
    m_string("")
{
    // Initialize value
    switch (m_type) {
        case TypeInt:     m_int    = 0;     break;
        case TypeUInt:    m_uint   = 0;     break;
        case TypeDouble:  m_double = 0.0;   break;
        case TypeBool:    m_bool   = false; break;
    }
}

Value::Value(int value) :
    m_type(TypeInt),
    m_string("")
{
    // Initialize value
    m_int = value;
}

Value::Value(unsigned int value) :
    m_type(TypeUInt),
    m_string("")
{
    // Initialize value
    m_uint = value;
}

Value::Value(double value) :
    m_type(TypeDouble),
    m_string("")
{
    // Initialize value
    m_double = value;
}

Value::Value(bool value) :
    m_type(TypeBool),
    m_string("")
{
    // Initialize value
    m_bool = value;
}

Value::Value(const std::string &value) :
    m_type(TypeString),
    m_string(value)
{
}

Value::Value(const std::vector<std::string> &values) :
    m_type(TypeArray),
    m_string("")
{
    for (std::vector<std::string>::const_iterator it = values.begin(); it != values.end(); ++it) {
        std::string value = *it;
        append(value);
    }
}

Value::Value(const char *value) :
    m_type(TypeString),
    m_string(value)
{
}

/**
*  @brief
*    Copy constructor
*/
Value::Value(const Value &rh)
{
    *this = rh;
}

/**
*  @brief
*    Destructor
*/
Value::~Value()
{
    m_array .clear();
    m_object.clear();
}

/**
*  @brief
*    Copy operator
*/
Value &Value::operator =(const Value &rh)
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
        }
    }

    // Return reference
    return *this;
}

/**
*  @brief
*    Clear all data
*/
void Value::clear()
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
Value::Type Value::type() const
{
    return m_type;
}

/**
*  @brief
*    Check if value is empty
*/
bool Value::empty() const
{
    return (  m_type == TypeNull ||
             (m_type == TypeObject    && m_object.empty()) ||
             (m_type == TypeArray     && m_array .empty()) );
}

/**
*  @brief
*    Convert value into integer
*/
int Value::toInt() const
{
    switch (m_type) {
        case TypeNull:      return 0;
        case TypeInt:       return m_int;
        case TypeUInt:      return (m_uint < MAX_INT) ? (int)m_uint : 0;
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
unsigned int Value::toUInt() const
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
double Value::toDouble() const
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
bool Value::toBool() const
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
std::string Value::toString() const
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
StringList Value::toStringList() const
{
    StringList list;

    // Array
    if (m_type == TypeArray) {
        // Convert each value into a string
        for (std::vector<Value>::const_iterator it = m_array.begin(); it != m_array.end(); ++it) {
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
std::string Value::toJSON(bool nice, const std::string &indent) const
{
    // Value is an object
    if (m_type == TypeObject) {
        // Quick output: {} if empty
        if (empty()) return "{}";

        // Begin output
        std::string json = "{";
        if (nice) json += "\n";

        // Add all variables
        bool first = true;
        for (std::map<std::string, Value>::const_iterator it = m_object.begin(); it != m_object.end(); ++it) {
            // Add separator (",")
            if (!first) json += nice ? ",\n" : ","; else first = false;

            // Get variable
            std::string name = it->first;
            const Value &var = it->second;

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

    // Value is an array
    else if (m_type == TypeArray) {
        // Quick output: [] if empty
        if (empty()) return "[]";

        // Begin output
        std::string json = "[";
        if (nice) json += "\n";

        // Add all elements
        bool first = true;
        for (std::vector<Value>::const_iterator it = m_array.begin(); it != m_array.end(); ++it) {
            // Add separator (",")
            if (!first) json += nice ? ",\n" : ","; else first = false;

            // Get variable
            const Value &var = *it;

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
bool Value::isObject() const
{
    return (m_type == TypeObject);
}

/**
*  @brief
*    Get list of object keys
*/
StringList Value::keys() const
{
    StringList keys;
    for (std::map<std::string, Value>::const_iterator it = m_object.begin(); it != m_object.end(); ++it)
        keys.push_back(it->first);
    return keys;
}

/**
*  @brief
*    Check if object contains an attribute
*/
bool Value::contains(const std::string &name) const
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
const Value &Value::get(const std::string &name) const
{
    // Only works on objects
    if (m_type == TypeObject && contains(name)) {
        return m_object.at(name);
    }

    // Error, return empty value
    return Value::Null;
}

/**
*  @brief
*    Get object attribute
*/
Value &Value::get(const std::string &name)
{
    // Only works on objects
    if (m_type == TypeObject && contains(name)) {
        return m_object.at(name);
    }

    // Error, return empty value
    return Value::Null;
}

/**
*  @brief
*    Get object attribute
*/
const Value &Value::operator [](const std::string &name) const
{
    return get(name);
}

/**
*  @brief
*    Get object attribute
*/
Value &Value::operator [](const std::string &name)
{
    // Only works on objects
    if (m_type == TypeObject && this != &Null) {
        // Check if attribute is present
        if (m_object.count(name) < 1) {
            // Append empty value
            Value v;
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
Value &Value::set(const std::string &name, const Value &value)
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
void Value::remove(const std::string &name)
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
bool Value::isArray() const
{
    return (m_type == TypeArray);
}

/**
*  @brief
*    Get size of array
*/
unsigned int Value::size() const
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
const Value &Value::get(unsigned int index) const
{
    // Only works on arrays
    if (m_type == TypeArray) {
        // Check if element exists, otherwise return empty value
        if (index < m_array.size())
            // Return a reference to the actual data, no copy
            return m_array[index];
    }

    // Error, return empty value
    return Value::Null;
}

/**
*  @brief
*    Get array element
*/
Value &Value::get(unsigned int index)
{
    // Only works on arrays
    if (m_type == TypeArray) {
        // Check if element exists, otherwise return empty value
        if (index < m_array.size())
            // Return a reference to the actual data, no copy
            return m_array[index];
    }

    // Error, return empty value
    return Value::Null;
}

/**
*  @brief
*    Get array element
*/
const Value &Value::operator [](unsigned int index) const
{
    return get(index);
}

/**
*  @brief
*    Get array element
*/
Value &Value::operator [](unsigned int index)
{
    return get(index);
}

/**
*  @brief
*    Set array element
*/
Value &Value::set(unsigned int index, const Value &value)
{
    // Only works on arrays
    if (m_type == TypeArray && this != &Null) {
        // Resize container if necessary
        if (index >= m_array.size())
            m_array.resize(index+1, Value::Null);

        // Set value
        m_array[index] = value;
    }

    return *this;
}

/**
*  @brief
*    Append element to array
*/
Value &Value::append(const Value &value)
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
Value &Value::append()
{
    // Only works on arrays
    if (m_type == TypeArray && this != &Null) {
        // Append empty value
        Value v;
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
void Value::remove(unsigned int index)
{
    // Only works on arrays
    if (m_type == TypeArray && this != &Null) {
        // Remove value
        if (index >= 0 && index < m_array.size())
            m_array.erase(m_array.begin() + index);
    }
}


} // namespace scriptzeug
