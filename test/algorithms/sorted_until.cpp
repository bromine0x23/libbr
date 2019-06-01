#include "test.hpp"

#include <libbr/algorithms/sorted_until.hpp>

using namespace BR;

TEST(Algorithms, sorted_until) {
	int array[] = { 4, 5, 9, 3, 1, 1 };

	EXPECT_EQ(array + 3, sorted_until(array, array + 6));
}
