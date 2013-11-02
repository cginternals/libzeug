
#include <iostream>

#include <stagezeug/AbstractStage.h>
#include <stagezeug/StageData.h>

namespace zeug 
{

StageData::StageData()
: m_valid(false)
{
}

StageData::~StageData()
{
}

const AbstractStage * StageData::owner() const
{
    return m_owner;
}

void StageData::setOwner(AbstractStage * owner)
{
	m_owner = owner;
}

bool StageData::isValid() const
{
    return m_valid;
}

void StageData::invalidate()
{
    m_valid = false;
    invalidated();
}

void StageData::setToValid()
{
    m_valid = true;
}

} // namespace zeug
