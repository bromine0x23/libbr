#include "test.hpp"

#include <libbr/algorithms/maxmin.hpp>

using namespace BR;

TEST(Algorithms, maxmin) {
	auto list = { 1, 4, 5, 2, 3 };
	auto comparator = [](int x, int y){ return y < x; };
	EXPECT_EQ((make_pair(5, 1)), maxmin(1, 5));
	EXPECT_EQ((make_pair(1, 5)), maxmin(1, 5, comparator));
	EXPECT_EQ((make_pair(5, 1)), Algorithms::maxmin(list));
	EXPECT_EQ((make_pair(1, 5)), Algorithms::maxmin(list, comparator));
}