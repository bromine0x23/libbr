#include "test.hpp"

#include <libbr/algorithms/max.hpp>

using namespace BR;

TEST(Algorithms, max) {
	auto list = { 1, 4, 5, 2, 3 };
	auto comparator = [](int x, int y){ return y < x; };
	EXPECT_EQ(5, max(1, 5));
	EXPECT_EQ(1, max(1, 5, comparator));
	EXPECT_EQ(5, Algorithms::max(list));
	EXPECT_EQ(1, Algorithms::max(list, comparator));
}