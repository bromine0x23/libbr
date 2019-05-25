#include "test.hpp"

#include <libbr/algorithms/remove.hpp>

using namespace BR;

TEST(Algorithms, remove) {
	int array[] = { 1, 2, 3, 4, 2, 2, 3, 4 };

	auto new_end = remove(array, array + 8, 2);

	EXPECT_EQ(5, new_end - array);

	EXPECT_EQ(1, array[0]);
	EXPECT_EQ(3, array[1]);
	EXPECT_EQ(4, array[2]);
	EXPECT_EQ(3, array[3]);
	EXPECT_EQ(4, array[4]);
}
