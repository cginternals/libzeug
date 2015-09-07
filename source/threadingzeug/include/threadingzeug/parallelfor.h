#pragma once

#include <functional>
#include <vector>

#include <threadingzeug/threadingzeug_api.h>

namespace threadingzeug
{

THREADINGZEUG_API void forEach(size_t start, size_t end, std::function<void(size_t i)> callback, bool parallelize = true);

using ForSignature = void (*)(size_t, size_t, std::function<void(size_t i)>);

template <typename T, typename U>
ForSignature selectParallelization(const T & value, const U & threshold);

THREADINGZEUG_API ForSignature selectParallelization(bool);

template<typename T>
void parallelFor(const std::vector<T>& elements, std::function<void(const T& element)> callback);

template<typename T>
void parallelFor(std::vector<T>& elements, std::function<void(T& element)> callback);

THREADINGZEUG_API void parallelFor(size_t start, size_t end, std::function<void(size_t i)> callback);


template<typename T>
void sequentialFor(const std::vector<T>& elements, std::function<void(const T& element)> callback);

template<typename T>
void sequentialFor(std::vector<T>& elements, std::function<void(T& element)> callback);

THREADINGZEUG_API void sequentialFor(size_t start, size_t end, std::function<void(size_t i)> callback);

} // namespace threadingzeug

#include <threadingzeug/parallelfor.hpp>
