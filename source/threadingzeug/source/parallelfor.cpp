
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

void forEach(size_t start, size_t end, std::function<void(size_t i)> callback, const bool parallelize)
{
    (parallelize ?
        static_cast<void(*)(size_t, size_t, std::function<void(size_t i)>)>(parallelFor) :
        static_cast<void(*)(size_t, size_t, std::function<void(size_t i)>)>(sequentialFor)
    )(start, end, callback);
}

void forEach(std::uint32_t start, std::uint32_t end, std::function<void(std::uint32_t i)> callback, const bool parallelize)
{
    (parallelize ?
        static_cast<void(*)(std::uint32_t, std::uint32_t, std::function<void(std::uint32_t i)>)>(parallelFor) :
        static_cast<void(*)(std::uint32_t, std::uint32_t, std::function<void(std::uint32_t i)>)>(sequentialFor)
    )(start, end, callback);
}

void parallelFor(size_t start, size_t end, std::function<void(size_t i)> callback)
{
#ifdef USE_OPENMP

    #pragma omp parallel for
    for (std::int64_t i = static_cast<std::int64_t>(start); i < static_cast<std::int64_t>(end); ++i)
    {
        callback(static_cast<std::size_t>(i));
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

void parallelFor(std::uint32_t start, std::uint32_t end, std::function<void(std::uint32_t i)> callback)
{
#ifdef USE_OPENMP

#pragma omp parallel for
    for (std::int64_t i = static_cast<std::int64_t>(start); i < static_cast<std::int64_t>(end); ++i)
    {
        callback(static_cast<std::uint32_t>(i));
    }

#else

    auto threads = std::vector<std::thread>(numberOfThreads);

    for (auto i = static_cast<std::uint32_t>(0); i < numberOfThreads; ++i)
    {
        threads[i] = std::thread([start, end, i, &callback]() {
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

void sequentialFor(std::uint32_t start, std::uint32_t end, std::function<void(std::uint32_t i)> callback)
{
    for (auto i = start; i < end; ++i)
    {
        callback(i);
    }
}

} // namespace threadingzeug
