#include "test.hpp"

#include <libbr/algorithms/find.hpp>

using namespace BR;

TEST(Algorithms, find) {
	int array[] = {0, 1, 2, 3, 4};

	EXPECT_EQ(3, *find(array, array + 5, 3));

	EXPECT_EQ(array + 5, find(array, array + 5, 5));
}
