#include "test.hpp"

#include <libbr/algorithms/partition_stably.hpp>

using namespace BR;

TEST(Algorithms, partition_stably) {
	int array[] = { 2, 1, 3, 4, 5, 6, 7, 8, 9 };

	auto is_even = [](int x){ return x % 2 == 0; };

	partition_stably(array, array + 9, is_even);

	EXPECT_EQ(2, array[0]);
	EXPECT_EQ(4, array[1]);
	EXPECT_EQ(6, array[2]);
	EXPECT_EQ(8, array[3]);
	EXPECT_EQ(1, array[4]);
	EXPECT_EQ(3, array[5]);
	EXPECT_EQ(5, array[6]);
	EXPECT_EQ(7, array[7]);
}
