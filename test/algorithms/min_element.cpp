#include "test.hpp"

#include <libbr/algorithms/min_element.hpp>

using namespace BR;

TEST(Algorithms, min_element) {
	auto compare_absolute = [](int x, int y){ return (x < 0 ? -x : x) < (y < 0 ? -y : y); };

	int array[] = { 3, 1, -14, 1, 5, -14, 9 };

	EXPECT_EQ(array + 2, min_element(array, array + 7));
	EXPECT_EQ(array + 1, min_element(array, array + 7, compare_absolute));
}