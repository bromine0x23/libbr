#include "../test.hpp"
#include <libbr/algorithm/max_min.hpp>

using namespace BR;

TEST(Algorithm, max_min) {
	auto comparator = [](auto x, auto y){ return y < x; };
	EXPECT_EQ((make_pair(5, 1)), max_min(1, 5));
	EXPECT_EQ((make_pair(1, 5)), max_min(1, 5, comparator));
	EXPECT_EQ((make_pair(5, 1)), max_min({ 1, 4, 5, 2, 3 }));
	EXPECT_EQ((make_pair(1, 5)), max_min({ 1, 4, 5, 2, 3 }, comparator));
}