
#include <stagezeug/AbstractStage.h>
#include <stagezeug/StageOutput.h>

namespace zeug 
{

AbstractStageOutput::AbstractStageOutput()
: m_owner(nullptr)
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

void AbstractStageOutput::invalidate()
{
    invalidated();
}

} // namespace zeug
