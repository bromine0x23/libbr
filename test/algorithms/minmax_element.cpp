#include "test.hpp"

#include <libbr/algorithms/minmax_element.hpp>

using namespace BR;

TEST(Algorithms, minmax_element) {
	auto compare_absolute = [](int x, int y) { return (x < 0 ? -x : x) < (y < 0 ? -y : y); };

	int array[] = {3, 1, -14, 1, 5, -14, 9};

	{
		auto pair = minmax_element(array, array + 7);
		EXPECT_EQ(array + 2, pair.first);
		EXPECT_EQ(array + 6, pair.second);
	}
	{
		auto pair = minmax_element(array, array + 7, compare_absolute);
		EXPECT_EQ(array + 1, pair.first);
		EXPECT_EQ(array + 5, pair.second);
	}
}