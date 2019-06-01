#include "test.hpp"

#include <libbr/algorithms/is_partitioned.hpp>

using namespace BR;

TEST(Algorithms, is_partitioned) {
	auto is_less_than_5 = [](int x){ return x < 5; };
	auto is_even = [](int x){ return x % 2 == 0; };

	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	EXPECT_TRUE(is_partitioned(array, array + 9, is_less_than_5));
	EXPECT_FALSE(is_partitioned(array, array + 9, is_even));
}
