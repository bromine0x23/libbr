#include "test.hpp"

#include <libbr/algorithms/uniquify.hpp>

using namespace BR;

TEST(Algorithms, uniquify) {
	int array[] = { 1, 1, 2, 2, 3, 1, 1, 2, 3 };

	auto new_end = uniquify(array, array + 9);

	EXPECT_EQ(array + 6, new_end);
	EXPECT_EQ(1, array[0]);
	EXPECT_EQ(2, array[1]);
	EXPECT_EQ(3, array[2]);
	EXPECT_EQ(1, array[3]);
	EXPECT_EQ(2, array[4]);
	EXPECT_EQ(3, array[5]);
}