#include "../test.hpp"
#include <libbr/algorithm/max.hpp>

using namespace BR;

TEST(Algorithm, max) {
	using BR::max;
	auto list = { 1, 4, 5, 2, 3 };
	auto comparator = [](int x, int y){ return y < x; };
	EXPECT_EQ(5, max(1, 5));
	EXPECT_EQ(1, max(1, 5, comparator));
	EXPECT_EQ(5, max(list));
	EXPECT_EQ(1, max(list, comparator));
}