#pragma once

namespace zeug 
{

template<typename T>
void parallel_for(const std::vector<T>& elements, std::function<void(const T& element)> callback)
{
	parallel_for(0, elements.size(), [callback, &elements](unsigned i) {
		callback(elements[i]);
	});
}

template<typename T>
void parallel_for(std::vector<T>& elements, std::function<void(T& element)> callback)
{
	parallel_for(0, elements.size(), [callback, &elements](unsigned i) {
		callback(elements[i]);
	});
}


template<typename T>
void sequential_for(const std::vector<T>& elements, std::function<void(const T& element)> callback)
{
	sequential_for(0, elements.size(), [callback, &elements](unsigned i) {
		callback(elements[i]);
	});
}

template<typename T>
void sequential_for(std::vector<T>& elements, std::function<void(T& element)> callback)
{
	sequential_for(0, elements.size(), [callback, &elements](unsigned i) {
		callback(elements[i]);
	});
}

} // namespace zeug
