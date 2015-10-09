
#include <reflectionzeug/function/Function.h>


namespace reflectionzeug
{


AbstractFunction::AbstractFunction(const std::string & name)
: m_name(name)
{
}

AbstractFunction::~AbstractFunction()
{
}

std::string AbstractFunction::name() const
{
    return m_name;
}


} // namespace reflectionzeug
