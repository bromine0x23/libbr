#include "test.hpp"

#include <libbr/algorithms/is_sorted.hpp>

using namespace BR;

TEST(Algorithms, is_sorted) {
	int array[] = { 1, 3, 4, 4, 9, 1 };

	EXPECT_TRUE(is_sorted(array, array + 5));
	EXPECT_FALSE(is_sorted(array, array + 6));
}
