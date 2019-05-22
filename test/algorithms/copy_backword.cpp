#include "test.hpp"

#include <libbr/algorithms/copy_backward.hpp>

using namespace BR;

TEST(Algorithms, copy_backward) {
	int from_array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int to_array[10] = {};

	copy_backward(from_array, from_array + 10, to_array + 10);

	EXPECT_EQ(0, to_array[0]);
	EXPECT_EQ(4, to_array[4]);
	EXPECT_EQ(9, to_array[9]);
}
