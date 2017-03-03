#include "../test.hpp"
#include <libbr/algorithm/min.hpp>

using namespace BR;

TEST(Algorithm, min) {
	auto comparator = [](auto x, auto y){ return y < x; };
	EXPECT_EQ(1, min(1, 5));
	EXPECT_EQ(5, min(1, 5, comparator));
	EXPECT_EQ(1, min({ 1, 4, 5, 2, 3 }));
	EXPECT_EQ(5, min({ 1, 4, 5, 2, 3 }, comparator));
}