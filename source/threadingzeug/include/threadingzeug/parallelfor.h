#pragma once

#include <functional>
#include <vector>
#include <cstddef>

#include <threadingzeug/threadingzeug_api.h>

namespace threadingzeug
{

THREADINGZEUG_API void forEach(
      size_t start
    , size_t end
    , std::function<void(size_t i)> callback
    , bool parallelize = true);

THREADINGZEUG_API void forEach(
      std::uint32_t start
    , std::uint32_t end
    , std::function<void(std::uint32_t i)> callback
    , bool parallelize = true);


template<typename T>
void parallelFor(const std::vector<T> & elements, std::function<void(const T & element)> callback);

template<typename T>
void parallelFor(std::vector<T> & elements, std::function<void(T & element)> callback);

THREADINGZEUG_API void parallelFor(
      size_t start
    , size_t end
    , std::function<void(size_t i)> callback);

THREADINGZEUG_API void parallelFor(
      std::uint32_t start
    , std::uint32_t end
    , std::function<void(std::uint32_t i)> callback);


template<typename T>
void sequentialFor(const std::vector<T> & elements, std::function<void(const T & element)> callback);

template<typename T>
void sequentialFor(std::vector<T> & elements, std::function<void(T & element)> callback);

THREADINGZEUG_API void sequentialFor(
      size_t start
    , size_t end
    , std::function<void(size_t i)> callback);

THREADINGZEUG_API void sequentialFor(
      std::uint32_t start
    , std::uint32_t end
    , std::function<void(std::uint32_t i)> callback);

} // namespace threadingzeug

#include <threadingzeug/parallelfor.hpp>
