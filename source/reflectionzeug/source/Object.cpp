#include "reflectionzeug/Object.h"


namespace reflectionzeug
{


Object::Object(const std::string & name)
: PropertyGroup(name)
{
}

Object::~Object()
{
    for (std::vector<AbstractFunction*>::iterator it = m_functions.begin(); it != m_functions.end(); ++it)
        delete (*it);
}

const std::vector<AbstractFunction *> & Object::functions() const
{
    return m_functions;
}


} // namespace reflectionzeug
