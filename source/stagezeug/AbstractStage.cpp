
#include <iostream>

#include <stagezeug/StageData.h>
#include <stagezeug/AbstractStage.h>

namespace zeug 
{

AbstractStage::AbstractStage(StageData * output)
: m_output(output)
, m_enabled(true)
{
	if (m_output)
	{
		m_output->setOwner(this);
	}
}

AbstractStage::~AbstractStage()
{
}

void AbstractStage::requireAll() 
{
}

const StageData * AbstractStage::output() const
{
    return m_output;
}

bool AbstractStage::execute()
{
    if (!m_enabled || (m_output && m_output->isValid()))
        return false;

    process();
    
    if (m_output)
	    m_output->setToValid();
    
    return true;
}

void AbstractStage::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

bool AbstractStage::isEnabled() const
{
    return m_enabled;
}

const std::string& AbstractStage::name() const
{
    return m_name;
}

void AbstractStage::setName(const std::string & name)
{
    m_name = name;
}

void AbstractStage::require(AbstractStage * stage)
{
	if (!stage)
		return;
	
	if (stage->dependsOn(this))
	{
		std::cout << "Circular dependency detected." << std::endl;
		return;
	}
	
	addInput(stage->output());
}

void AbstractStage::addInput(const StageData * input)
{
    if (!input)
        return;

    m_inputs.insert(input);
    input->invalidated.connect([this]() {
        invalidateOutput();
    });

    inputAdded(input);
    dependenciesChanged();
}

void AbstractStage::inputAdded(const StageData * input)
{
}

void AbstractStage::invalidateOutput()
{
        if (m_output)
            m_output->invalidate();
}

bool AbstractStage::dependsOn(const AbstractStage * stage) const
{
    for (const StageData * input: m_inputs)
    {
        const AbstractStage* inputOwner = input->owner();
        if (!inputOwner)
            continue;

        if (inputOwner == stage || inputOwner->dependsOn(stage))
            return true;
    }

    return false;
}

} // namespace zeug
