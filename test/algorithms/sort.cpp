#include "test.hpp"

#include <libbr/algorithms/sort.hpp>

using namespace BR;

TEST(Algorithms, sort) {
	int array[] = { 9, 6, 0, 7, 10, 8, 11, 12, 13, 15, 5, 4, 3, 14, 1, 2 };

	sort(array, array + 16);

	for (int i = 0; i <= 15; ++i) {
		EXPECT_EQ(i, array[i]);
	}
}
