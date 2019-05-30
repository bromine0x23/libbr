#include "test.hpp"

#include <libbr/algorithms/replace_if.hpp>

using namespace BR;

TEST(Algorithms, replace_if) {
	auto is_even = [](int x){ return x % 2 == 0; };

	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	replace_if(array, array + 9, is_even, 100);

	EXPECT_EQ(  1, array[0]);
	EXPECT_EQ(100, array[1]);
	EXPECT_EQ(  3, array[2]);
	EXPECT_EQ(100, array[3]);
	EXPECT_EQ(  5, array[4]);
	EXPECT_EQ(100, array[5]);
	EXPECT_EQ(  7, array[6]);
	EXPECT_EQ(100, array[7]);
	EXPECT_EQ(  9, array[8]);
}
