#include "test.hpp"

#include <libbr/algorithms/find_if.hpp>

using namespace BR;

TEST(Algorithms, find_if) {
	int array[] = {0, 1, 2, 3, 4};

	EXPECT_EQ(3, *find_if(array, array + 5, [](int x){ return x > 2; }));
	EXPECT_EQ(array + 5, find_if(array, array + 5, [](int x){ return x > 4; }));
}
