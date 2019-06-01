#include "test.hpp"

#include <libbr/algorithms/merge.hpp>

#include <libbr/algorithms/is_sorted.hpp>

using namespace BR;

TEST(Algorithms, merge) {
	int source0[] = { 0, 2, 4, 6, 7 };
	int source1[] = { 1, 3, 5, 8, 9 };
	int target[10];

	auto end = merge(source0, source0 + 5, source1, source1 + 5, target);

	EXPECT_EQ(target + 10, end);
	EXPECT_TRUE(is_sorted(target, end));
}
