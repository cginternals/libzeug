#include <stagezeug/Pipeline.h>

#include <algorithm>

namespace zeug {

Pipeline::Pipeline()
{
}

Pipeline::~Pipeline()
{
}

void Pipeline::addStage(AbstractStage* stage)
{
    _stages.push_back(stage);
    stage->dependenciesChanged.connect([this]() { sortDependencies(); });
    sortDependencies();
}

void Pipeline::execute()
{
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
}

} // namespace zeug
