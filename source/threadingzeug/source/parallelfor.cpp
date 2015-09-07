
#include <thread>
#include <vector>
#include <algorithm>

#include <threadingzeug/parallelfor.h>

namespace
{
#ifndef USE_OPENMP

    const auto numberOfThreads = std::max(static_cast<size_t>(2), static_cast<size_t>(std::thread::hardware_concurrency()));

#endif
}

namespace threadingzeug
{

void forEach(size_t start, size_t end, std::function<void(size_t i)> callback, bool parallelize)
{
    selectParallelization(parallelize)(start, end, callback);
}

ForSignature selectParallelization(bool parallelize)
{
    return parallelize ?
        static_cast<void (*)(size_t, size_t, std::function<void(size_t i)>)>(parallelFor) :
        static_cast<void (*)(size_t, size_t, std::function<void(size_t i)>)>(sequentialFor);
}

void parallelFor(size_t start, size_t end, std::function<void(size_t i)> callback)
{
#ifdef USE_OPENMP

    #pragma omp parallel for
    for (auto i = start; i < end; ++i)
    {
        callback(i);
    }

#else

    auto threads = std::vector<std::thread>(numberOfThreads);
	
    for (auto i = static_cast<size_t>(0); i < numberOfThreads; ++i)
	{
        threads[i] = std::thread([start, end, i, &callback] () {
            for (auto k = start + i; k < end; k += numberOfThreads)
            {
                callback(k);
            }
        });
	}

	for (auto & thread : threads)
    {
		thread.join();
    }

#endif
}

void sequentialFor(size_t start, size_t end, std::function<void(size_t i)> callback)
{
    for (auto i = start; i < end; ++i)
	{
		callback(i);
	}
}

} // namespace threadingzeug
