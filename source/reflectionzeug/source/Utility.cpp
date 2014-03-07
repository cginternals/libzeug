
#ifdef USE_STD_REGEX
    #include <regex>

    namespace regex_namespace = std;
#else
    #include <boost/regex.hpp>

    namespace regex_namespace = boost;
#endif

#include <reflectionzeug/Utility.h>

namespace reflectionzeug
{

namespace util
{

bool matchesRegex(const std::string & string, const std::string & regex)
{
    return regex_namespace::regex_match(string, regex_namespace::regex(regex));
}

std::vector<std::string> extract(const std::string & string, const std::string & regex)
{
    std::vector<std::string> values;

    regex_namespace::smatch matchResults;
    regex_namespace::regex_search(string, matchResults, regex_namespace::regex(regex));

    for (const std::string & match : matchResults)
    {
        values.push_back(match);
    }

    return values;
}

} // namespace util

} // namespace reflectionzeug
