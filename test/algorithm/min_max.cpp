#include "../test.hpp"
#include <libbr/algorithm/min_max.hpp>

using namespace BR;

TEST(Algorithm, min_max) {
	auto comparator = [](auto x, auto y){ return y < x; };
	EXPECT_EQ((make_pair(1, 5)), min_max(1, 5));
	EXPECT_EQ((make_pair(5, 1)), min_max(1, 5, comparator));
	EXPECT_EQ((make_pair(1, 5)), min_max({ 1, 4, 5, 2, 3 }));
	EXPECT_EQ((make_pair(5, 1)), min_max({ 1, 4, 5, 2, 3 }, comparator));
}