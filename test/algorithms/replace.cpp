#include "test.hpp"

#include <libbr/algorithms/replace.hpp>

using namespace BR;

TEST(Algorithms, replace) {
	int array[] = { 1, 2, 3, 4, 2, 2, 3, 4 };

	replace(array, array + 8, 2, 22);

	EXPECT_EQ( 1, array[0]);
	EXPECT_EQ(22, array[1]);
	EXPECT_EQ( 3, array[2]);
	EXPECT_EQ( 4, array[3]);
	EXPECT_EQ(22, array[4]);
	EXPECT_EQ(22, array[5]);
	EXPECT_EQ( 3, array[6]);
	EXPECT_EQ( 4, array[7]);
}
