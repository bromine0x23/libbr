#include "test.hpp"

#include <libbr/algorithms/uniquify_copy.hpp>

using namespace BR;

TEST(Algorithms, uniquify_copy) {
	int source[] = { 1, 1, 2, 2, 3, 1, 1, 2, 3 };

	int target[9] = {};

	auto end = uniquify_copy(source, source + 9, target);

	EXPECT_EQ(target + 6, end);
	EXPECT_EQ(1, target[0]);
	EXPECT_EQ(2, target[1]);
	EXPECT_EQ(3, target[2]);
	EXPECT_EQ(1, target[3]);
	EXPECT_EQ(2, target[4]);
	EXPECT_EQ(3, target[5]);
}