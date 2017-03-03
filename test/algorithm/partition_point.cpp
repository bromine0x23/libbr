#include "../test.hpp"
#include <libbr/algorithm/partition_point.hpp>

#include <libbr/algorithm/partition.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, partition_point) {
	DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	auto is_even = [](int x){ return x % 2 == 0; };

	auto pivot = partition(array.begin(), array.end(), is_even);

	EXPECT_EQ(pivot, partition_point(array.cbegin(), array.cend(), is_even));
}
