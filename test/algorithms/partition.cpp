#include "test.hpp"

#include <libbr/algorithms/partition.hpp>

#include <libbr/algorithms/all_of.hpp>
#include <libbr/algorithms/none_of.hpp>

using namespace BR;

TEST(Algorithms, partition) {
	auto is_even = [](int x){ return x % 2 == 0; };

	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	auto pivot = partition(array, array + 9, is_even);

	EXPECT_TRUE(all_of(array, pivot, is_even));

	EXPECT_TRUE(none_of(pivot, array + 9, is_even));
}
