#include "test.hpp"

#include <libbr/algorithms/copy_n.hpp>

using namespace BR;

TEST(Algorithms, copy_n) {
	int source[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int target[9];

	EXPECT_EQ(target + 5, copy_n(source, 5, target));
	EXPECT_EQ(1, target[0]);
	EXPECT_EQ(2, target[1]);
	EXPECT_EQ(3, target[2]);
	EXPECT_EQ(4, target[3]);
	EXPECT_EQ(5, target[4]);
}
