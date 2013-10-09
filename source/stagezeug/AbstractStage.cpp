#include <stagezeug/AbstractStage.h>

namespace zeug {

AbstractStage::AbstractStage(ExecutionPolicy policy)
: _policy(policy)
, _enabled(true)
, _valid(false)
{
}

AbstractStage::~AbstractStage()
{
}

bool AbstractStage::execute()
{
	if (needsToExecute())
	{
		process();
		_valid = true;

		return true;
	}

	return false;
}

bool AbstractStage::needsToExecute() const
{
    if (!_enabled)
        return false;

    switch (_policy)
    {
        case WhenInvalid:
            return !_valid;
        case Always:
            return true;
        case Never:
            return false;
        default:
            return false;
    }
}

void AbstractStage::invalidate()
{
	for (AbstractStage* dependentStage : _dependentStages)
	{
		dependentStage->invalidate();
	}

    _valid = false;

	invalidated();
}

bool AbstractStage::isValid() const
{
    return _valid;
}

void AbstractStage::setEnabled(bool enabled)
{
    _enabled = enabled;
}

bool AbstractStage::isEnabled() const
{
    return _enabled;
}

void AbstractStage::setExecutionPolicy(ExecutionPolicy policy)
{
    _policy = policy;
}

AbstractStage::ExecutionPolicy AbstractStage::policy() const
{
    return _policy;
}

const std::string& AbstractStage::name() const
{
    return _name;
}

void AbstractStage::setName(const std::string& name)
{
    _name = name;
}

void AbstractStage::invalidated()
{
}

void AbstractStage::addRequiredStage(AbstractStage* stage)
{
	if (!stage) return;

	_requiredStages.insert(stage);
	stage->addDependentStage(this);

    dependenciesChanged();
}

void AbstractStage::addDependentStage(AbstractStage* stage)
{
	if (!stage) return;

	_dependentStages.insert(stage);
}

bool AbstractStage::requires(const AbstractStage* stage) const
{
    for (const AbstractStage* requirement: _requiredStages)
    {
        if (requirement == stage || requirement->requires(stage))
            return true;
    }

    return false;
}

} // namespace zeug
