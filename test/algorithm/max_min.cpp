#include "../test.hpp"
#include <libbr/algorithm/max_min.hpp>

using namespace BR;

TEST(Algorithm, max_min) {
	using BR::max_min;
	auto list = { 1, 4, 5, 2, 3 };
	auto comparator = [](int x, int y){ return y < x; };
	EXPECT_EQ((make_pair(5, 1)), max_min(1, 5));
	EXPECT_EQ((make_pair(1, 5)), max_min(1, 5, comparator));
	EXPECT_EQ((make_pair(5, 1)), max_min(list));
	EXPECT_EQ((make_pair(1, 5)), max_min(list, comparator));
}