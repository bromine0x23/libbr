#include "test.hpp"

#include <libbr/algorithms/copy.hpp>

using namespace BR;

TEST(Algorithms, copy) {
	int from_array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int to_array[10] = {};

	copy(from_array, from_array + 10, to_array);

	EXPECT_EQ(0, to_array[0]);
	EXPECT_EQ(5, to_array[5]);
	EXPECT_EQ(9, to_array[9]);
}
