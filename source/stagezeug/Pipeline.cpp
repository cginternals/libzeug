#include <stagezeug/Pipeline.h>

#include <algorithm>

namespace zeug {

Pipeline::Pipeline()
: _dependenciesSorted(false)
{
}

Pipeline::~Pipeline()
{
}

void Pipeline::addStage(AbstractStage* stage)
{
    _stages.push_back(stage);
    stage->dependenciesChanged.connect([this]() { _dependenciesSorted = false; });
}

void Pipeline::execute()
{
    if (!_dependenciesSorted)
    {
        sortDependencies();
    }
	
    for (AbstractStage* stage: _stages)
    {
        stage->execute();
    }
}

void Pipeline::sortDependencies()
{
    std::sort(_stages.begin(), _stages.end(), [](AbstractStage* stage1, AbstractStage* stage2) {
        return stage2->requires(stage1);
    });
    _dependenciesSorted = true;
}

} // namespace zeug
