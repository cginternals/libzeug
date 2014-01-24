#include <scriptzeug/Scriptable.h>


namespace scriptzeug
{


Scriptable::Scriptable(const std::string & name)
: PropertyGroup(name)
{
}

Scriptable::~Scriptable()
{
    for (std::vector<AbstractFunction*>::iterator it = m_functions.begin(); it != m_functions.end(); ++it)
        delete (*it);
}

const std::vector<AbstractFunction *> & Scriptable::functions() const
{
    return m_functions;
}


} // namespace
