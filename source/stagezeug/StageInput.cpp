
#include <iostream>

#include <stagezeug/AbstractStage.h>
#include <stagezeug/StageInput.h>

namespace zeug
{

AbstractStageInput::AbstractStageInput()
: m_hasChanged(false)
, m_owner(nullptr)
{
}

AbstractStageInput::~AbstractStageInput()
{
}

const AbstractStage * AbstractStageInput::owner() const
{
    return m_owner;
}

void AbstractStageInput::setOwner(AbstractStage * owner)
{
    m_owner = owner;
}

bool AbstractStageInput::hasChanged() const
{
    return m_hasChanged;
}

void AbstractStageInput::changed()
{
    m_hasChanged = true;
}

void AbstractStageInput::processed()
{
    m_hasChanged = false;
}


} // namespace zeug
