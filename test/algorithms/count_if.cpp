#include "test.hpp"

#include <libbr/algorithms/count_if.hpp>

using namespace BR;

TEST(Algorithms, count_if) {
	int array[] = { 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };

	EXPECT_EQ(3, count_if(array, array + 10, [](int x){ return x % 3 == 0; }));
}
