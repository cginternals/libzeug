#pragma once

#include <threadingzeug/parallelfor.h>

namespace threadingzeug
{

template<typename T>
void parallelFor(const std::vector<T> & elements, std::function<void(const T & element)> callback)
{
    parallelFor(0, elements.size(), [callback, &elements](size_t i) {
		callback(elements[i]);
	});
}

template<typename T>
void parallelFor(std::vector<T> & elements, std::function<void(T & element)> callback)
{
    parallelFor(0, elements.size(), [callback, &elements](size_t i) {
		callback(elements[i]);
	});
}


template<typename T>
void sequentialFor(const std::vector<T> & elements, std::function<void(const T & element)> callback)
{
    sequentialFor(0, elements.size(), [callback, &elements](size_t i) {
		callback(elements[i]);
	});
}

template<typename T>
void sequentialFor(std::vector<T>& elements, std::function<void(T& element)> callback)
{
    sequentialFor(0, elements.size(), [callback, &elements](size_t i) {
		callback(elements[i]);
	});
}

} // namespace threadingzeug
