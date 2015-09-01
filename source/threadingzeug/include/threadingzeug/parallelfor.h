#pragma once

#include <functional>
#include <vector>

#include <threadingzeug/threadingzeug_api.h>

namespace threadingzeug
{

THREADINGZEUG_API void forEach(int start, int end, std::function<void(int i)> callback, bool parallelize = true);

using ForSignature = void (*)(int, int, std::function<void(int i)>);

template <typename T, typename U>
ForSignature selectParallelization(const T & value, const U & threshold);

THREADINGZEUG_API ForSignature selectParallelization(bool);

template<typename T>
void parallelFor(const std::vector<T>& elements, std::function<void(const T& element)> callback);

template<typename T>
void parallelFor(std::vector<T>& elements, std::function<void(T& element)> callback);

THREADINGZEUG_API void parallelFor(int start, int end, std::function<void(int i)> callback);


template<typename T>
void sequentialFor(const std::vector<T>& elements, std::function<void(const T& element)> callback);

template<typename T>
void sequentialFor(std::vector<T>& elements, std::function<void(T& element)> callback);

THREADINGZEUG_API void sequentialFor(int start, int end, std::function<void(int i)> callback);

} // namespace threadingzeug

#include <threadingzeug/parallelfor.hpp>
