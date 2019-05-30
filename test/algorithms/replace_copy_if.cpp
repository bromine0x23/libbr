#include "test.hpp"

#include <libbr/algorithms/replace_copy_if.hpp>

using namespace BR;

TEST(Algorithms, replace_copy_if) {
	auto is_even = [](int x){ return x % 2 == 0; };

	int source[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int replaced[9] = {};

	auto end = replace_copy_if(source, source + 9, replaced, is_even, 100);

	EXPECT_EQ(end, replaced + 9);

	EXPECT_EQ(  1, replaced[0]);
	EXPECT_EQ(100, replaced[1]);
	EXPECT_EQ(  3, replaced[2]);
	EXPECT_EQ(100, replaced[3]);
	EXPECT_EQ(  5, replaced[4]);
	EXPECT_EQ(100, replaced[5]);
	EXPECT_EQ(  7, replaced[6]);
	EXPECT_EQ(100, replaced[7]);
	EXPECT_EQ(  9, replaced[8]);
}
