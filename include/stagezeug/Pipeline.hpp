#pragma once

namespace zeug 
{

template<typename T, typename... Args>
void Pipeline::addStages(T stage, Args... stages)
{
	addStage(stage);
	addStages(stages...);
}

} // namespace zeug
