#include "test.hpp"

#include <libbr/algorithms/find_unless.hpp>

using namespace BR;

TEST(Algorithms, find_unless) {
	int array[] = {0, 1, 2, 3, 4};

	EXPECT_EQ(3, *find_unless(array, array + 5, [](int x){ return x < 3; }));
	EXPECT_EQ(array + 5, find_unless(array, array + 5, [](int x){ return x <  5; }));
}
