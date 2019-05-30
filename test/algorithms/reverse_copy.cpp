#include "test.hpp"

#include <libbr/algorithms/reverse_copy.hpp>

using namespace BR;

TEST(Algorithms, reverse_copy) {
	int source[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int target[10];

	reverse_copy(source, source + 10, target);

	EXPECT_EQ(9, target[0]);
	EXPECT_EQ(5, target[4]);
	EXPECT_EQ(4, target[5]);
	EXPECT_EQ(0, target[9]);
}
