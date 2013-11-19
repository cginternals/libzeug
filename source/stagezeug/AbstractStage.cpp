
#include <iostream>
#include <algorithm>

#include <stagezeug/StageInput.h>
#include <stagezeug/StageOutput.h>
#include <stagezeug/AbstractStage.h>

namespace zeug 
{

AbstractStage::AbstractStage()
: m_enabled(true)
{
}

AbstractStage::~AbstractStage()
{
}

bool AbstractStage::execute()
{
    if (!m_enabled || !needsToProcess())
        return false;

    if (!allInputsConnected())
    {
        std::cout << "Inputs are not connected." << std::endl;
        return false;
    }

    process();
    
    validateOutputs();
    validateInputs();
    
    return true;
}

bool AbstractStage::needsToProcess() const
{
    return m_inputs.empty() || std::any_of(m_inputs.begin(), m_inputs.end(), [](const AbstractStageInput * input) {
        return input->hasChanged();
    });
}

bool AbstractStage::allInputsConnected() const
{
    return std::all_of(m_inputs.begin(), m_inputs.end(), [](const AbstractStageInput * input) {
        return input->isOptional() || input->isConnected();
    });
}

void AbstractStage::validateOutputs()
{
    for (AbstractStageOutput * output : m_outputs)
    {
        output->validate();
    }
}

void AbstractStage::validateInputs()
{
    for (AbstractStageInput * input : m_inputs)
    {
        input->processed();
    }
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

bool AbstractStage::dependsOn(const AbstractStage * stage) const
{
    for (AbstractStageInput * input : m_inputs)
    {
        const AbstractStage* owner = input->owner();
        if (!owner)
            continue;

        if (owner == stage || owner->dependsOn(stage))
            return true;
    }

    return false;
}

void AbstractStage::addOutput(AbstractStageOutput & output)
{
    output.setOwner(this);
    m_outputs.insert(&output);
}

void AbstractStage::addInput(AbstractStageInput & input)
{
    input.setOwner(this);
    m_inputs.insert(&input);
}

} // namespace zeug
