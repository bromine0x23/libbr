#include "test.hpp"

#include <libbr/algorithms/min.hpp>

using namespace BR;

TEST(Algorithms, min) {
	auto list = { 1, 4, 5, 2, 3 };
	auto comparator = [](int x, int y){ return y < x; };
	EXPECT_EQ(1, min(1, 5));
	EXPECT_EQ(5, min(1, 5, comparator));
	EXPECT_EQ(1, Algorithms::min(list));
	EXPECT_EQ(5, Algorithms::min(list, comparator));
}