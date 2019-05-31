#include "test.hpp"

#include <libbr/algorithms/find_in.hpp>

using namespace BR;

TEST(Algorithms, find_in) {
	int array[] = { 0, 2, 3, 25, 5 };

	int elements[] = { 3, 19, 10, 2 };

	EXPECT_EQ(array + 1, find_in(array, array + 5, elements, elements + 4));

	EXPECT_EQ(array + 2, find_in(array, array + 5, elements, elements + 3));

	EXPECT_EQ(array + 5, find_in(array, array + 5, elements + 1, elements + 3));
}
