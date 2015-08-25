
#include <thread>
#include <vector>
#include <algorithm>

#include <threadingzeug/parallelfor.h>

namespace threadingzeug
{

void forEach(int start, int end, std::function<void(int i)> callback, bool parallelize)
{
    selectParallelization(parallelize)(start, end, callback);
}

ForSignature selectParallelization(bool parallelize)
{
    return parallelize ?
        static_cast<void (*)(int, int, std::function<void(int i)>)>(parallelFor) :
        static_cast<void (*)(int, int, std::function<void(int i)>)>(sequentialFor);
}

void parallelFor(int start, int end, std::function<void(int i)> callback)
{
#ifdef USE_OPENMP

    #pragma omp parallel for
    for (int i = start; i < end; ++i)
        callback(i);

#else

    const auto numberOfThreads = std::max(2, static_cast<int>(std::thread::hardware_concurrency()));
	std::vector<std::thread> threads(numberOfThreads);
	
	for (auto i = 0; i < numberOfThreads; ++i)
	{
		threads[i] = std::thread([numberOfThreads, start, end, i, &callback] ()
            {
                for (auto k = start + i; k < end; k += numberOfThreads)
                    callback(k);
            });
	}

	for (auto & thread : threads)
		thread.join();

#endif
}

void sequentialFor(int start, int end, std::function<void(int i)> callback)
{
	for (int i = start; i < end; ++i)
	{
		callback(i);
	}
}

} // namespace threadingzeug
