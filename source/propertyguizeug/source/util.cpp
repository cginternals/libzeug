#include "util.h"

namespace propertyguizeug
{

namespace util
{

QStringList toQStringList(const std::vector<std::string> & list)
{
    auto qlist = QStringList{};
    for (auto string : list)
        qlist << QString::fromStdString(string);
    return qlist;
}

} // namespace util

} // namespace propertyguizeug
