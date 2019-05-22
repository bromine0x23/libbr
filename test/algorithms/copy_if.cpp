#include "test.hpp"

#include <libbr/algorithms/copy_if.hpp>

using namespace BR;

TEST(Algorithms, copy_if) {
	int from_array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	decltype(from_array) to_array = {};

	auto is_even = [](int x){ return x % 2 == 0; };

	copy_if(from_array, from_array + 10, to_array, is_even);

	EXPECT_EQ(2, to_array[0]);
	EXPECT_EQ(4, to_array[1]);
	EXPECT_EQ(6, to_array[2]);
	EXPECT_EQ(8, to_array[3]);
	EXPECT_EQ(10, to_array[4]);
}
