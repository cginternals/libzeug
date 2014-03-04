#include <scriptzeug/Backend/AbstractScriptContext.h>


namespace scriptzeug
{


AbstractScriptContext::AbstractScriptContext(ScriptContext * scriptContext)
: m_scriptContext(scriptContext)
{
}

AbstractScriptContext::~AbstractScriptContext()
{
}


} // namespace scriptzeug
