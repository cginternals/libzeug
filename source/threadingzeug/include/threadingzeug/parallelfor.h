#pragma once

#include <functional>
#include <vector>

#include <threadingzeug/threadingzeug.h>

namespace threadingzeug
{

template<typename T>
THREADINGZEUG_API void parallel_for(const std::vector<T>& elements, std::function<void(const T& element)> callback);

template<typename T>
THREADINGZEUG_API void parallel_for(std::vector<T>& elements, std::function<void(T& element)> callback);

THREADINGZEUG_API void parallel_for(int start, int end, std::function<void(int i)> callback);


template<typename T>
THREADINGZEUG_API void sequential_for(const std::vector<T>& elements, std::function<void(const T& element)> callback);

template<typename T>
THREADINGZEUG_API void sequential_for(std::vector<T>& elements, std::function<void(T& element)> callback);

THREADINGZEUG_API void sequential_for(int start, int end, std::function<void(int i)> callback);

} // namespace threadingzeug

#include <threadingzeug/parallelfor.hpp>
