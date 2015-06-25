
#include <reflectionzeug/tools/SerializerINI.h>

#include <sstream>

#ifdef USE_STD_REGEX
    #include <regex>
    namespace regex_namespace = std;
#else
    #include <boost/regex.hpp>
    namespace regex_namespace = boost;
#endif

#include <reflectionzeug/base/util.h>
#include <reflectionzeug/property/AbstractProperty.h>


namespace reflectionzeug {


SerializerINI::SerializerINI()
: m_rootOutput(nullptr)
, m_currentOut(nullptr)
{
}

SerializerINI::~SerializerINI()
{
}

bool SerializerINI::fromString(Variant & obj, const std::string & string)
{
    // Set output value
    m_rootOutput = &obj;
    m_currentOut = &obj;

    // Read file line by line
    std::stringstream stream(string);
    std::string line;
    while (std::getline(stream, line)) {
        parseLine(line);
    }

    // [TODO]
    return false;
}

std::string SerializerINI::toString(const Variant & obj)
{
    // Check if variant is a group
    if (!obj.isMap() && !obj.isArray()) {
        return "";
    }

    // Clear data
    m_pathStack.clear();
    m_stream.clear();

    // Serialize variant
    serializeGroup("", obj);

    // Return string
    return m_stream.str();
}

void SerializerINI::serializeGroup(const std::string & name, const Variant & value)
{
    // Begin category
    if (!name.empty()) {
        m_pathStack.push_back(name);
    }

    // Write category marker
    std::string category = currentPath();
    if (!category.empty()) {
        m_stream << "[" << category << "]" << std::endl;
    }

    // Serialize child values
    if (value.isMap()) {
        // Variant map
        const VariantMap & map = *(value.asMap());

        // Serialize all values
        for (auto it : map) {
            std::string     subName  = it.first;
            const Variant & subValue = it.second;
            if (!subValue.isMap() && !subValue.isArray()) {
                serializeValue(subName, subValue);
            }
        }

        // Add separator
        m_stream << std::endl;

        // Serialize all groups
        for (auto it : map) {
            std::string     subName  = it.first;
            const Variant & subValue = it.second;
            if (subValue.isMap() || subValue.isArray()) {
                serializeGroup(subName, subValue);
            }
        }
    } else if (value.isArray()) {
        // Variant array
        const VariantArray & array = *(value.asArray());

        // Serialize all values
        for (size_t i=0; i<array.size(); i++) {
            std::string     subName  = "_" + util::toString(i);
            const Variant & subValue = array[i];
            if (!subValue.isMap() && !subValue.isArray()) {
                serializeValue(subName, subValue);
            }
        }

        // Add separator
        m_stream << std::endl;

        // Serialize all groups
        for (size_t i=0; i<array.size(); i++) {
            std::string     subName  = "_" + util::toString(i);
            const Variant & subValue = array[i];
            if (subValue.isMap() || subValue.isArray()) {
                serializeGroup(subName, subValue);
            }
        }
    }

    // End category
    if (!name.empty()) {
        m_pathStack.pop_back();
    }
}

void SerializerINI::serializeValue(const std::string & name, const Variant & value)
{
    m_stream << name << "=" << value.value<std::string>() << std::endl;
}

std::string SerializerINI::currentPath() const
{
    std::stringstream stream;

    bool first = true;
    for (const std::string & name : m_pathStack) {
        if (!first) stream << "/";
        else        first = false;
        stream << name;
    }

    return stream.str();
}

void SerializerINI::parseLine(const std::string & line)
{
    // Check type of line
    bool isGroup = isGroupDeclaration(line);
    bool isValue = isPropertyDeclaration(line);

    // Enter group
    if (isGroup) {
        parseGroup(line);
    }

    // Parse value
    else if (isValue) {
        parseValue(line);
    }
}

void SerializerINI::parseGroup(const std::string & line)
{
    // Get group path
    std::string path = line.substr(1, line.length() - 2);

    // Split path into components
    std::vector<std::string> names = util::split(path, '/');

    // Get variant leaf node, create variants in between if necessary
    m_currentOut = m_rootOutput;
    for (std::string name : names) {
        m_currentOut = getSubValue(*m_currentOut, name);
        if (!m_currentOut)
            break;
    }
}

void SerializerINI::parseValue(const std::string & line)
{
    // Check if current group is valid
    if (!m_currentOut) {
        return;
    }

    // Get name and value
    regex_namespace::smatch match;
    regex_namespace::regex_search(line, match, regex_namespace::regex("="));
    std::string name  = match.prefix();
    std::string value = match.suffix();

    // Get output variant
    Variant * out = getSubValue(*m_currentOut, name);
    if (out) {
        // Set value
        *out = Variant(value);
    }
}

bool SerializerINI::isGroupDeclaration(const std::string & line)
{
    static const regex_namespace::regex groupRegex("\\[" + AbstractProperty::s_nameRegexString + "\\]");

    return regex_namespace::regex_match(line, groupRegex);
}

bool SerializerINI::isPropertyDeclaration(const std::string & line)
{
    static const regex_namespace::regex propertyRegex(AbstractProperty::s_nameRegexString +
                                          "(\\/" +
                                          AbstractProperty::s_nameRegexString +
                                          ")*=.+");

    return regex_namespace::regex_match(line, propertyRegex);
}

Variant * SerializerINI::getSubValue(Variant & var, const std::string & name)
{
    static const regex_namespace::regex arrayRegex("_\\d+");

    // Check type of container based on the name of the child
    if (regex_namespace::regex_match(name, arrayRegex)) {
        // Name suggests that var has to be an array
        if (!var.isArray()) {
            // If var is empty, create an array, other return with error
            if (var.isNull()) {
                var = Variant::array();
            } else {
                return nullptr;
            }
        }

        // Get array
        VariantArray & array = *(var.asArray());

        // Check if a value exists
        unsigned int index = util::fromString<unsigned int>(name.substr(1));
        if (index >= array.size()) {
            // Create new empty value
            array.push_back(Variant());
        }

        // Return variant
        return &(array[index]);
    } else {
        // Name suggests that var has to be a map
        if (!var.isMap()) {
            // If var is empty, create a map, other return with error
            if (var.isNull()) {
                var = Variant::map();
            } else {
                return nullptr;
            }
        }

        // Get map
        VariantMap & map = *(var.asMap());

        // Check if a value exists
        if (map.count(name) <= 0) {
            // Create new empty value
            map[name] = Variant();
        }

        // Return variant
        return &(map[name]);
    }
}


} // namespace reflectionzeug
