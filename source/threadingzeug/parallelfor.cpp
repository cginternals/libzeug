
#include <thread>
#include <vector>

#include <threadingzeug/parallelfor.h>

namespace zeug 
{

void parallel_for(int start, int end, std::function<void(int i)> callback)
{
#ifdef USE_OPENMP

    #pragma omp parallel for
    for (int i = start; i < end; ++i)
        callback(i);

#else


    const int numberOfThreads = std::max(2, static_cast<int>(std::thread::hardware_concurrency()));
	std::vector<std::thread> threads(numberOfThreads);
	
	for (int i = 0; i < numberOfThreads; ++i)
	{
		threads[i] = std::thread([numberOfThreads, start, end, i, callback]()
        { 
            for (int k = start + i; k < end - start; k += numberOfThreads)
				callback(k + start);
		});
	}

	for (std::thread & thread : threads)
		thread.join();

#endif
}

void sequential_for(int start, int end, std::function<void(int i)> callback)
{
	for (int i = start; i < end; ++i)
	{
		callback(i);
	}
}

} // namespace zeug
