#include <stagezeug/AbstractStage.h>
#include <iostream>

namespace zeug {

StageData::StageData()
: _valid(false)
{
}

StageData::~StageData()
{
}

const AbstractStage* StageData::owner() const
{
    return _owner;
}

void StageData::setOwner(AbstractStage* owner)
{
	_owner = owner;
}

bool StageData::isValid() const
{
    return _valid;
}

void StageData::invalidate()
{
    _valid = false;
    invalidated();
}

void StageData::setToValid()
{
    _valid = true;
}


AbstractStage::AbstractStage(StageData* output)
: _output(output)
, _enabled(true)
{
	if (_output)
	{
		_output->setOwner(this);
	}
}

AbstractStage::~AbstractStage()
{
}

const StageData* AbstractStage::output() const
{
    return _output;
}

bool AbstractStage::execute()
{
    if (!_enabled || (_output && _output->isValid()))
        return false;

    process();
    
    if (_output)
	    _output->setToValid();
    
    return true;
}

void AbstractStage::setEnabled(bool enabled)
{
    _enabled = enabled;
}

bool AbstractStage::isEnabled() const
{
    return _enabled;
}

const std::string& AbstractStage::name() const
{
    return _name;
}

void AbstractStage::setName(const std::string& name)
{
    _name = name;
}

void AbstractStage::require(AbstractStage* stage)
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

void AbstractStage::addInput(const StageData* input)
{
    if (!input)
        return;

    _inputs.insert(input);
    input->invalidated.connect([this]() {
        invalidateOutput();
    });

    inputAdded(input);
    dependenciesChanged();
}

void AbstractStage::inputAdded(const StageData* input)
{
}

void AbstractStage::invalidateOutput()
{
        if (_output)
            _output->invalidate();
}

bool AbstractStage::dependsOn(const AbstractStage* stage) const
{
    for (const StageData* input: _inputs)
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
