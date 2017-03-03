#include "../test.hpp"
#include <libbr/algorithm/partition_stably.hpp>

#include <libbr/algorithm/partition.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, partition_stably) {
	DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	auto is_even = [](int x){ return x % 2 == 0; };

	partition_stably(array.begin(), array.end(), is_even);

	EXPECT_EQ((DynamicArray<int>{ 2, 4, 6, 8, 1, 3, 5, 7, 9 }), array);
}
