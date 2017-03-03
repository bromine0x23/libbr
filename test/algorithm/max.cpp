#include "../test.hpp"
#include <libbr/algorithm/max.hpp>

using namespace BR;

TEST(Algorithm, max) {
	auto comparator = [](auto x, auto y){ return y < x; };
	EXPECT_EQ(5, max(1, 5));
	EXPECT_EQ(1, max(1, 5, comparator));
	EXPECT_EQ(5, max({ 1, 4, 5, 2, 3 }));
	EXPECT_EQ(1, max({ 1, 4, 5, 2, 3 }, comparator));
}