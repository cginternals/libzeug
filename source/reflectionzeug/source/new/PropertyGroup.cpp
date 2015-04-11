
#include <reflectionzeug/new/PropertyGroup.h>


namespace reflectionzeug
{


PropertyGroup2::PropertyGroup2(const std::string & name)
: AbstractProperty2(name)
{
}

PropertyGroup2::~PropertyGroup2()
{
}

std::string PropertyGroup2::name() const
{
    return m_name;
}

bool PropertyGroup2::setName(const std::string & name)
{
    m_name = name;
    return true;
}


} // namespace reflectionzeug
