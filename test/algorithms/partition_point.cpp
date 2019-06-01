#include "test.hpp"

#include <libbr/algorithms/partition_point.hpp>

#include <libbr/algorithms/partition.hpp>

using namespace BR;

TEST(Algorithms, partition_point) {
	auto is_even = [](int x){ return x % 2 == 0; };

	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	auto pivot = partition(array, array + 9, is_even);

	EXPECT_EQ(pivot, partition_point(array, array + 9, is_even));
}
