#include <reflectionzeug/util.h>

#include <cctype>
#include <cassert>
#include <algorithm>

#include <reflectionzeug/regex_namespace.h>

namespace reflectionzeug
{

namespace util
{

template <>
char fromString<char>(const std::string & string)
{
    std::stringstream stream(string);
    int value;
    stream >> value;
    return static_cast<char>(value);
}

template <>
unsigned char fromString<unsigned char>(const std::string & string)
{
    std::stringstream stream(string);
    unsigned int value;
    stream >> value;
    return static_cast<unsigned char>(value);
}

template <>
std::string toString<char>(const char & value)
{
    std::stringstream stream;
    stream << static_cast<int>(value);
    return stream.str();
}

template <>
std::string toString<unsigned char>(const unsigned char & value)
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

std::vector<std::string> splitArray(size_t size, const std::string & string)
{
    std::string regexString = "\\s*\\(";
    for (size_t i = 0; i < size - 1; ++i)
        regexString.append("([^,]*),");
    regexString.append("([^,]*)\\)\\s*");

    regex_namespace::smatch match;
    regex_namespace::regex regex(regexString);

    if (!regex_namespace::regex_match(string, match, regex))
        return {};

    std::vector<std::string> result;
    for (size_t i = 1; i < match.size(); ++i)
        result.push_back(trim(match[i].str(), false));

    assert(result.size() == size);
    return result;
}
    
std::vector<std::string> split(const std::string & input, char delimiter)
{
    std::vector<std::string> result;
    result.push_back(std::string());
    for (const char & c : input)
	{
		if (c == delimiter)
		{
			result.push_back(std::string());
			continue;
		}
		
		result.back().push_back(c);
	}
	return result;
}

} // namespace util

} // namespace reflectionzeug
