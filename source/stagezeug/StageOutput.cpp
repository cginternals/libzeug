
#include <stagezeug/AbstractStage.h>
#include <stagezeug/StageOutput.h>

namespace zeug 
{

AbstractStageOutput::AbstractStageOutput()
: m_valid(false)
, m_owner(nullptr)
{
}

AbstractStageOutput::~AbstractStageOutput()
{
}

const AbstractStage * AbstractStageOutput::owner() const
{
    return m_owner;
}

void AbstractStageOutput::setOwner(AbstractStage * owner)
{
	m_owner = owner;
}

bool AbstractStageOutput::isValid() const
{
    return m_valid;
}

void AbstractStageOutput::invalidate()
{
    m_valid = false;
    invalidated();
}

void AbstractStageOutput::validate()
{
    m_valid = true;
}

} // namespace zeug
