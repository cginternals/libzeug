#include <gmock/gmock.h>

#include <thread>

#include <threadingzeug/parallelfor.h>


using namespace threadingzeug;

class parallel_for_test : public testing::Test
{
public:
    parallel_for_test()
    {
    }

protected:
};

TEST_F(parallel_for_test, IncrementVector)
{
    const auto start = 3, end = 27;
    auto vec = std::vector<int>(27, 0);

    parallel_for(start, end, [&vec] (int i)
        {
            std::this_thread::sleep_for(std::chrono::nanoseconds{1000000});
            vec[i] = 1;
        });

    auto allTrue = true;

    for (auto i = start; i < end; ++i)
        allTrue &= (vec[i] == 1);

    ASSERT_TRUE(allTrue);
}
