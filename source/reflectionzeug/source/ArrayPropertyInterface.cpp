
#include <reflectionzeug/ArrayPropertyInterface.h>

namespace reflectionzeug
{

ArrayPropertyInterface::ArrayPropertyInterface(const std::string & name)
:   ValuePropertyInterface(name)
{
}

bool ArrayPropertyInterface::isArray() const
{
    return true;
}

} // namespace reflectionzeug
