#include "test.hpp"

#include <libbr/algorithms/count.hpp>

using namespace BR;

TEST(Algorithms, count) {
	int array[] = { 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };

	EXPECT_EQ(2, count(array, array + 10, 3));
	EXPECT_EQ(0, count(array, array + 10, 5));
}
