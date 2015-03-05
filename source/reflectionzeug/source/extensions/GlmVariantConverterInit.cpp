
#include <reflectionzeug/extensions/GlmVariantConverterInit.h>

#include <reflectionzeug/regex_namespace.h>

namespace reflectionzeug
{

void initializeGlmVariantConverters()
{
    GlmVariantConverterInit<glm::vec2>()();
    GlmVariantConverterInit<glm::ivec2>()();
    GlmVariantConverterInit<glm::vec3>()();
    GlmVariantConverterInit<glm::ivec3>()();
    GlmVariantConverterInit<glm::vec4>()();
    GlmVariantConverterInit<glm::ivec4>()();

    registerStringToGlmConverters();
}

void registerStringToGlmConverters()
{
    static const std::string r_ulonglong = "(?:0|[1-9]\\d*)";
    static const std::string r_longlong = "-?" + r_ulonglong;
    static const std::string r_number = r_longlong + "(?:\\.\\d+)?";

    static const regex_namespace::regex vec2Regex(
            "^\"\\( ?(" + r_number + "), (" + r_number + ") ?\\)\"$");
    Variant::registerConverter<std::string, glm::vec2>(
        [](const std::string & str) -> glm::vec2
            {
                regex_namespace::smatch match;
                regex_namespace::regex_match(str, match, vec2Regex);
                return glm::vec2(util::fromString<double>(match[1]), util::fromString<double>(match[2]));
            }
    );

    static const regex_namespace::regex ivec2Regex(
            "^\"\\( ?(" + r_longlong + "), (" + r_longlong + ") ?\\)\"$");
    Variant::registerConverter<std::string, glm::ivec2>(
        [](const std::string & str) -> glm::ivec2
            {
                regex_namespace::smatch match;
                regex_namespace::regex_match(str, match, ivec2Regex);
                return glm::ivec2(util::fromString<int>(match[1]), util::fromString<int>(match[2]));
            }
    );

    static const regex_namespace::regex vec3Regex(
            "^\"\\( ?(" + r_number + "), (" + r_number + "), (" + r_number + ") ?\\)\"$");
    Variant::registerConverter<std::string, glm::vec3>(
        [](const std::string & str) -> glm::vec3
            {
                regex_namespace::smatch match;
                regex_namespace::regex_match(str, match, vec3Regex);
                return glm::vec3(util::fromString<double>(match[1]),
                        util::fromString<double>(match[2]),
                        util::fromString<double>(match[3]));
            }
    );

    static const regex_namespace::regex ivec3Regex(
            "^\"\\( ?(" + r_longlong + "), (" + r_longlong + "), (" + r_longlong + ") ?\\)\"$");
    Variant::registerConverter<std::string, glm::ivec3>(
        [](const std::string & str) -> glm::ivec3
            {
                regex_namespace::smatch match;
                regex_namespace::regex_match(str, match, ivec3Regex);
                return glm::ivec3(util::fromString<int>(match[1]),
                        util::fromString<int>(match[2]),
                        util::fromString<int>(match[3]));
            }
    );

    static const regex_namespace::regex vec4Regex(
            "^\"\\( ?(" + r_number + "), (" + r_number + "), (" + r_number + "), (" + r_number + ") ?\\)\"$");
    Variant::registerConverter<std::string, glm::vec4>(
        [](const std::string & str) -> glm::vec4
            {
                regex_namespace::smatch match;
                regex_namespace::regex_match(str, match, vec4Regex);
                return glm::vec4(util::fromString<double>(match[1]),
                        util::fromString<double>(match[2]),
                        util::fromString<double>(match[3]),
                        util::fromString<double>(match[4]));
            }
    );

    static const regex_namespace::regex ivec4Regex(
            "^\"\\( ?(" + r_longlong + "), (" + r_longlong + "), (" + r_longlong + "), (" + r_longlong + ") ?\\)\"$");
    Variant::registerConverter<std::string, glm::ivec4>(
        [](const std::string & str) -> glm::ivec4
            {
                regex_namespace::smatch match;
                regex_namespace::regex_match(str, match, ivec4Regex);
                return glm::ivec4(util::fromString<int>(match[1]),
                        util::fromString<int>(match[2]),
                        util::fromString<int>(match[3]),
                        util::fromString<int>(match[4]));
            }
    );
}

} // namespace reflectionzeug
