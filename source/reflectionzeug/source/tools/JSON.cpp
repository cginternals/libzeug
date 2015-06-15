
#include <reflectionzeug/tools/JSON.h>

#include <fstream>
#include <sstream>

#include <reflectionzeug/tools/JSONReader.h>


namespace reflectionzeug {


bool JSON::parse(Variant & obj, const std::string & json)
{
    JSONReader reader;
    bool ok = reader.parse(json, obj);
    if (!ok) {
        // qDebug() << reader.getErrors();
    }
    return ok;
}

std::string JSON::stringify(const Variant & obj, bool nice, const std::string & indent)
{
    // Primitive data types
    if (obj.hasType<bool>()) {
        return obj.value<bool>() ? "true" : "false";
    } else if (obj.hasType<char>()) {
        std::stringstream s;
        s << obj.value<char>();
        return s.str();
    } else if (obj.hasType<unsigned char>()) {
        std::stringstream s;
        s << obj.value<unsigned char>();
        return s.str();
    } else if (obj.hasType<short>()) {
        std::stringstream s;
        s << obj.value<short>();
        return s.str();
    } else if (obj.hasType<unsigned short>()) {
        std::stringstream s;
        s << obj.value<unsigned short>();
        return s.str();
    } else if (obj.hasType<int>()) {
        std::stringstream s;
        s << obj.value<int>();
        return s.str();
    } else if (obj.hasType<unsigned int>()) {
        std::stringstream s;
        s << obj.value<unsigned int>();
        return s.str();
    } else if (obj.hasType<long>()) {
        std::stringstream s;
        s << obj.value<long>();
        return s.str();
    } else if (obj.hasType<unsigned long>()) {
        std::stringstream s;
        s << obj.value<unsigned long>();
        return s.str();
    } else if (obj.hasType<long long>()) {
        std::stringstream s;
        s << obj.value<long long>();
        return s.str();
    } else if (obj.hasType<unsigned long long>()) {
        std::stringstream s;
        s << obj.value<unsigned long long>();
        return s.str();
    } else if (obj.hasType<float>()) {
        std::stringstream s;
        s << obj.value<float>();
        return s.str();
    } else if (obj.hasType<double>()) {
        std::stringstream s;
        s << obj.value<double>();
        return s.str();
    } else if (obj.hasType<std::string>()) {
        return obj.value<std::string>();
    }

    // Variant is an object
    else if (obj.isMap()) {
        // Quick output: {} if empty
        if (obj.toMap()->empty()) return "{}";

        // Begin output
        std::string json = "{";
        if (nice) json += "\n";

        // Add all variables
        bool first = true;
        for (auto it : *obj.toMap()) {
            // Add separator (",")
            if (!first) json += nice ? ",\n" : ","; else first = false;

            // Get variable
            std::string name    = it.first;
            const Variant & var = it.second;

            // Get value
            std::string value;
            if (var.isMap() || var.isArray()) {
                value = stringify(var, nice, indent + "    ");
            } else if (var.isNull()) {
                value = "null";
            } else {
                value = escapeString(stringify(var));
                if (var.hasType<std::string>()) {
                    value = "\"" + value + "\"";
                }
            }

            // Add value to JSON
            json += (nice ? (indent + "    \"" + name + "\": " + value) : ("\"" + name + "\":" + value));
        }

        // Finish JSON
        json += (nice ? "\n" + indent + "}" : "}");
        return json;
    }

    // Variant is an array
    else if (obj.isArray()) {
        // Quick output: [] if empty
        if (obj.toArray()->empty()) return "[]";

        // Begin output
        std::string json = "[";
        if (nice) json += "\n";

        // Add all elements
        bool first = true;
        for (auto it = obj.toArray()->begin(); it != obj.toArray()->end(); ++it) {
            // Add separator (",")
            if (!first) json += nice ? ",\n" : ","; else first = false;

            // Get variable
            const Variant & var = *it;

            // Get value
            std::string value;
            if (var.isMap() || var.isArray()) {
                value = stringify(var, nice, indent + "    ");
            } else if (var.isNull()) {
                value = "null";
            } else {
                value = escapeString(stringify(var));
                if (var.hasType<std::string>()) {
                    value = "\"" + value + "\"";
                }
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

bool JSON::load(Variant & obj, const std::string & filename)
{
    // Open file
    std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
    if (in) {
        // Read file content
        std::string content;
        in.seekg(0, std::ios::end);
        content.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&content[0], content.size());
        in.close();

        // Parse JSON
        return parse(obj, content);
    }

    // Error
    return false;
}

void JSON::save(const Variant & obj, const std::string & filename, bool nice)
{
    // Open file
    std::ofstream out(filename.c_str(), std::ios::out | std::ios::trunc);
    if (out) {
        // Write JSON to file
        out << stringify(obj, nice);
        out.close();
    }
}

std::string JSON::escapeString(const std::string & in)
{
    std::string out = "";

    for (std::string::const_iterator it = in.begin(); it != in.end(); ++it) {
        unsigned char c = *it;
        if (c >= ' ' and c <= '~' and c != '\\' and c != '"') {
            out.append(1, c);
        } else {
            out = out + '\\';
            switch(c) {
                case '"':  out = out + "\"";  break;
                case '\\': out = out + "\\"; break;
                case '\t': out = out + "t";  break;
                case '\r': out = out + "r";  break;
                case '\n': out = out + "n";  break;
                default:
                    char const* const hexdig = "0123456789ABCDEF";
                    out = out + "x";
                    out.append(1, hexdig[c >> 4]);
                    out.append(1, hexdig[c & 0xF]);
                    break;
            }
        }
    }

    return out;
}


} // namespace reflectionzeug
