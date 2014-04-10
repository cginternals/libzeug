
#ifdef USE_STD_REGEX
    #include <regex>

    namespace regex_namespace = std;
#else
    #include <boost/regex.hpp>

    namespace regex_namespace = boost;
#endif

#include <algorithm>
#include <cctype>

#include <reflectionzeug/util.h>

namespace reflectionzeug
{

namespace util
{

template <>
char fromString(const std::string & string)
{
    std::stringstream stream(string);
    int value;
    stream >> value;
    return static_cast<char>(value);
}

template <>
unsigned char fromString(const std::string & string)
{
    std::stringstream stream(string);
    unsigned int value;
    stream >> value;
    return static_cast<unsigned char>(value);
}

template <>
std::string toString(const char & value)
{
    std::stringstream stream;
    stream << static_cast<int>(value);
    return stream.str();
}

template <>
std::string toString(const unsigned char & value)
{
    std::stringstream stream;
    stream << static_cast<unsigned int>(value);
    return stream.str();
}

bool matchesRegex(const std::string & string, const std::string & regex)
{
    return regex_namespace::regex_match(string, regex_namespace::regex(regex));
}

std::vector<std::string> extract(const std::string & string, const std::string & regex)
{
    std::vector<std::string> values;

    regex_namespace::smatch matchResults;

    std::string s = string;
    while (regex_namespace::regex_search(s, matchResults, regex_namespace::regex(regex)))
    {
        values.push_back(matchResults[0]);
        s = matchResults.suffix().str();
    };

    return values;
}

std::string trim(const std::string & string, bool enclosed)
{
    const regex_namespace::regex regex(enclosed ? "\\s+" : "(^\\s+|\\s+$)");
    
    return regex_namespace::regex_replace(string, regex, "");
}

} // namespace util

} // namespace reflectionzeug
