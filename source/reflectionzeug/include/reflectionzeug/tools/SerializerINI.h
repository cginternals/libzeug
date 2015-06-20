
#pragma once


#include <deque>
#include <sstream>

#include <reflectionzeug/tools/Serializer.h>


namespace reflectionzeug {


/**
*  @brief
*    INI serializer
*
*  @remarks
*    The INI file format is not able to preserve the type of a variable,
*    so when loading from an INI file, all values will be strings.
*/
class REFLECTIONZEUG_API SerializerINI : public Serializer
{
public:
    /**
    *  @brief
    *    Constructor
    */
    SerializerINI();

    /**
    *  @brief
    *    Constructor
    */
    virtual ~SerializerINI();

    // Virtual Serializer interface
    virtual bool fromString(Variant & obj, const std::string & string) override;
    virtual std::string toString(const Variant & obj) override;


protected:
    // Serialization helpers
    void serializeGroup(const std::string & name, const Variant & value);
    void serializeValue(const std::string & name, const Variant & value);
    std::string currentPath() const;

    // Deserialization helpers
    void parseLine(const std::string & line);
    void parseGroup(const std::string & line);
    void parseValue(const std::string & line);
    bool isGroupDeclaration(const std::string & line);
    bool isPropertyDeclaration(const std::string & line);
    Variant * getSubValue(Variant & var, const std::string & name);


protected:
    // Serialization status
    std::deque<std::string> m_pathStack;
    std::stringstream       m_stream;

    // Deserialization status
    Variant * m_rootOutput;
    Variant * m_currentOut;
};


} // namespace reflectionzeug
