#include "test.hpp"

#include <libbr/algorithms/reverse.hpp>

using namespace BR;

TEST(Algorithms, reverse) {
	int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	reverse(array, array + 10);

	EXPECT_EQ(9, array[0]);
	EXPECT_EQ(5, array[4]);
	EXPECT_EQ(4, array[5]);
	EXPECT_EQ(0, array[9]);
}
