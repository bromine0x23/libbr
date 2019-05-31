#include "test.hpp"

#include <libbr/algorithms/rotate_copy.hpp>

using namespace BR;

TEST(Algorithms, rotate_copy) {
	int source[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int target[9];

	rotate_copy(source, source + 4, source + 9, target);

	EXPECT_EQ(5, target[0]);
	EXPECT_EQ(9, target[4]);
	EXPECT_EQ(1, target[5]);
	EXPECT_EQ(4, target[8]);
}
