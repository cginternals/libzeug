#pragma once

namespace zeug 
{

template <typename T, typename... Args>
void AbstractStage::requireAll(T* stage, Args... rest)
{
    require(stage);
    requireAll(rest...);
}


} // namespace zeug
