#pragma once


#include <string>
#include <vector>
#include <map>
#include <scriptzeug/scriptzeug.h>


namespace scriptzeug {


typedef std::vector<std::string> StringList;


/** \brief A value, object or array
 */
class SCRIPTZEUG_API Value {


public:
    /**
    *  @brief
    *    Empty, read-only value
    */
    static Value Null;

    /**
    *  @brief
    *    Create an empty object
    *
    *  @return
    *    Object
    */
    static Value Object();

    /**
    *  @brief
    *    Create an empty array
    *
    *  @return
    *    Array value
    */
    static Value Array();


public:
    /**
    *  @brief
    *    Value type
    */
    enum Type
    {
        TypeNull = 0,   /**< Null/invalid */
        TypeInt,        /**< Signed integer */
        TypeUInt,       /**< Unsigned integer */
        TypeDouble,     /**< Double */
        TypeBool,       /**< Boolean */
        TypeString,     /**< String */
        TypeArray,      /**< Array (ordered list of values) */
        TypeObject      /**< Object (name/value map) */
    };


public:
    /**
    *  @brief
    *    Constructor
    */
    Value(Type type = TypeNull);
    Value(int value);
    Value(unsigned int value);
    Value(double value);
    Value(bool value);
    Value(const std::string &value);
    Value(const std::vector<std::string> &values);
    Value(const char *value);

    /**
    *  @brief
    *    Copy constructor
    *
    *  @param[in] rh
    *    Right-handed value
    */
    Value(const Value &rh);

    /**
    *  @brief
    *    Destructor
    */
    ~Value();

    /**
    *  @brief
    *    Copy operator
    *
    *  @param[in] rh
    *    Right-hand value
    */
    Value &operator =(const Value &rh);

    /**
    *  @brief
    *    Clear all data
    */
    void clear();

    /**
    *  @brief
    *    Get type of value
    *
    *  @return
    *    Type
    */
    Type type() const;

    /**
    *  @brief
    *    Check if value is empty
    *
    *  @return
    *    'true' if empty array, empty object or null, else 'false'
    */
    bool empty() const;

    /**
    *  @brief
    *    Convert value into integer
    *
    *  @return
    *    Integer value, 0 on error
    */
    int toInt() const;

    /**
    *  @brief
    *    Convert value into unsigned integer
    *
    *  @return
    *    Unsigned integer value, 0 on error
    */
    unsigned int toUInt() const;

    /**
    *  @brief
    *    Convert value into double
    *
    *  @return
    *    Double value, 0.0 on error
    */
    double toDouble() const;

    /**
    *  @brief
    *    Convert value into boolean
    *
    *  @return
    *    Boolean value, false on error
    */
    bool toBool() const;

    /**
    *  @brief
    *    Convert value into string
    *
    *  @return
    *    String value, false on error
    */
    std::string toString() const;

    /**
    *  @brief
    *    Convert value to string list
    *
    *  @return
    *    String list
    */
    StringList toStringList() const;

    /**
    *  @brief
    *    Convert value to JSON notation
    *
    *  @param[in] nice
    *    Produce nice readable output?
    *  @param[in] indent
    *    Indendation string, used on the start of every new line
    *
    *  @return
    *    JSON representation
    *
    *  @remarks
    *    Only object or arrays can be converted into JSON, for every other type, "" is returned.
    *    Use toString() to convert a value of any type into a string.
    */
    std::string toJSON(bool nice = false, const std::string &indent = "") const;


    // Object interface

    /**
    *  @brief
    *    Check if value is an object
    *
    *  @return
    *    'true' if value is an object, else 'false'
    */
    bool isObject() const;

    /**
    *  @brief
    *    Get list of object keys
    *
    *  @return
    *    Object keys
    */
    StringList keys() const;

    /**
    *  @brief
    *    Check if object contains an attribute
    *
    *  @param[in] name
    *    Attribute name
    *
    *  @return
    *    'true' if object contains an attribute with that name, else 'false'
    */
    bool contains(const std::string &name) const;

    /**
    *  @brief
    *    Get object attribute
    *
    *  @param[in] name
    *    Attribute name
    *
    *  @return
    *    Value
    */
    const Value &get(const std::string &name) const;

    /**
    *  @brief
    *    Get object attribute
    *
    *  @param[in] name
    *    Attribute name
    *
    *  @return
    *    Value
    */
    Value &get(const std::string &name);

    /**
    *  @brief
    *    Get object attribute
    *
    *  @param[in] name
    *    Attribute name
    *
    *  @return
    *    Value
    */
    const Value &operator [](const std::string &name) const;

    /**
    *  @brief
    *    Get object attribute
    *
    *  @param[in] name
    *    Attribute name
    *
    *  @return
    *    Value
    *
    *  @remarks
    *    If the given key does not exist, an empty attribute is appended
    *    to the object.
    */
    Value &operator [](const std::string &name);

    /**
    *  @brief
    *    Set object attribute
    *
    *  @param[in] name
    *    Attribute name
    *  @param[in] value
    *    Value
    */
    Value &set(const std::string &name, const Value &value);

    /**
    *  @brief
    *    Remove object attribute
    *
    *  @param[in] name
    *    Attribute name
    */
    void remove(const std::string &name);


    // Array interface

    /**
    *  @brief
    *    Check if value is an array
    *
    *  @return
    *    'true' if value is an array, else 'false'
    */
    bool isArray() const;

    /**
    *  @brief
    *    Get size of array
    *
    *  @return
    *    Number of elements in array, 0 on error
    */
    unsigned int size() const;

    /**
    *  @brief
    *    Get array element
    *
    *  @param[in] index
    *    Index
    *
    *  @return
    *    Value
    */
    const Value &get(unsigned int index) const;

    /**
    *  @brief
    *    Get array element
    *
    *  @param[in] index
    *    Index
    *
    *  @return
    *    Value
    */
    Value &get(unsigned int index);

    /**
    *  @brief
    *    Get array element
    *
    *  @param[in] index
    *    Index
    *
    *  @return
    *    Value
    */
    const Value &operator [](unsigned int index) const;

    /**
    *  @brief
    *    Get array element
    *
    *  @param[in] index
    *    Index
    *
    *  @return
    *    Value
    */
    Value &operator [](unsigned int index);

    /**
    *  @brief
    *    Set array element
    *
    *  @param[in] index
    *    Index
    *  @param[in] value
    *    Value
    */
    Value &set(unsigned int index, const Value &value);

    /**
    *  @brief
    *    Append element to array
    *
    *  @param[in] value
    *    Value
    */
    Value &append(const Value &value);

    /**
    *  @brief
    *    Append new element to array
    *
    *  @return
    *    New value
    */
    Value &append();

    /**
    *  @brief
    *    Remove array element
    *
    *  @param[in] index
    *    Index
    */
    void remove(unsigned int index);


private:
    Type                         m_type;      /**< Type of value */
    union {
        int                      m_int;       /**< Signed integer value */
        unsigned int             m_uint;      /**< Unsigned integer value */
        double                   m_double;    /**< Double value */
        bool                     m_bool;      /**< Boolean value */
        Value                   *m_obj;       /**< Object pointer */
    };
    std::string                  m_string;    /**< String value */
    std::vector<Value>           m_array;     /**< Array value (ordered list of values) */
    std::map<std::string, Value> m_object;    /**< Object values */


};


} // namespace scriptzeug
