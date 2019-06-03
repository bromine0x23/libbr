#include "test.hpp"

#include <libbr/algorithms/minmax.hpp>

using namespace BR;

TEST(Algorithms, minmax) {
	auto list = { 1, 4, 5, 2, 3 };
	auto comparator = [](int x, int y){ return y < x; };
	EXPECT_EQ((make_pair(1, 5)), minmax(1, 5));
	EXPECT_EQ((make_pair(5, 1)), minmax(1, 5, comparator));
	EXPECT_EQ((make_pair(1, 5)), Algorithms::minmax(list));
	EXPECT_EQ((make_pair(5, 1)), Algorithms::minmax(list, comparator));
}