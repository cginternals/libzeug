#include <threadingzeug/parallelfor.h>

#include <thread>
#include <vector>

namespace zeug {

void parallel_for(int start, int end, std::function<void(int i)> callback)
{
#ifdef USE_OPENMP
	#pragma omp parallel for
	for (unsigned i=start; i < end; ++i)
	{
		callback(i);
	}
#else
	unsigned numberOfThreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads(numberOfThreads);
	
	for (unsigned i=0; i < numberOfThreads; ++i)
	{
		threads[i] = std::thread([numberOfThreads, start, end, i, callback]() {
			for (unsigned k=start+i; k<end-start; k+=numberOfThreads)
			{
				callback(k+start);
			}
		});
	}
	
	for (std::thread& thread : threads)
	{
		thread.join();
	}
#endif
}

} // namespace zeug
