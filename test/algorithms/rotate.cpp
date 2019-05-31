#include "test.hpp"

#include <libbr/algorithms/rotate.hpp>

using namespace BR;

TEST(Algorithms, rotate) {
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	rotate(array, array + 4, array + 9);

	EXPECT_EQ(5, array[0]);
	EXPECT_EQ(9, array[4]);
	EXPECT_EQ(1, array[5]);
	EXPECT_EQ(4, array[8]);
}
