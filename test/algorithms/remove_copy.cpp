#include "test.hpp"

#include <libbr/algorithms/remove_copy.hpp>

using namespace BR;

TEST(Algorithms, remove_copy) {
	int array[] = { 1, 2, 3, 4, 2, 2, 3, 4 };

	int removed[8] = {};

	auto end = remove_copy(array, array + 8, removed, 2);

	EXPECT_EQ(5, end - removed);

	EXPECT_EQ(1, removed[0]);
	EXPECT_EQ(3, removed[1]);
	EXPECT_EQ(4, removed[2]);
	EXPECT_EQ(3, removed[3]);
	EXPECT_EQ(4, removed[4]);
}
