
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
    if (!m_enabled)
        return false;

    if (!inputsUsable())
    {
        std::cout << "Some inputs might not be connected." << std::endl;
        return false;
    }

    if (needsToProcess())
        process();
    else
        return false;
    
    markInputsProcessed();
    
    return true;
}

bool AbstractStage::needsToProcess() const
{
    return m_inputs.empty() || std::any_of(m_inputs.begin(), m_inputs.end(), [](const AbstractStageInput * input) {
        return input->hasChanged();
    });
}

bool AbstractStage::inputsUsable() const
{
    return std::all_of(m_inputs.begin(), m_inputs.end(), [](const AbstractStageInput * input) {
        return input->isUsable() || input->isOptional();
    });
}

void AbstractStage::markInputsProcessed()
{
    for (AbstractStageInput * input : m_inputs)
    {
        input->processed();
    }
}

void AbstractStage::invalidateOutputs()
{
    for (AbstractStageOutput * output : m_outputs)
    {
        output->invalidate();
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

void AbstractStage::require(const AbstractStage * stage)
{
    m_required.insert(stage);
    dependenciesChanged();
}

bool AbstractStage::requires(const AbstractStage * stage) const
{
    for (const AbstractStage * requiredStage : m_required)
    {
        if (requiredStage == stage || requiredStage->requires(stage))
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
