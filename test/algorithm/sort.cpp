#include "../test.hpp"
#include <libbr/algorithm/sort.hpp>

#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, sort) {
	DynamicArray<int> array{ 9, 6, 0, 7, 10, 8, 11, 12, 13, 15, 5, 4, 3, 14, 1, 2 };

	sort(array.begin(), array.end());

	EXPECT_EQ((DynamicArray<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }), array);
}
