
#include <threadingzeug/parallelfor.h>


namespace threadingzeug
{


int getNumberOfThreads()
{
	return std::max(static_cast<size_t>(2), static_cast<size_t>(std::thread::hardware_concurrency()));
}


} // namespace threadingzeug
