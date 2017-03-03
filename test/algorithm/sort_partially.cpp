#include "../test.hpp"
#include <libbr/algorithm/sort_partially.hpp>

#include <libbr/algorithm/is_sorted.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, sort_partially) {
	DynamicArray<int> array{ 9, 6, 0, 7, 10, 8, 11, 12, 13, 15, 5, 4, 3, 14, 1, 2 };

	auto pivot = 7;

	sort_partially(array.begin(), array.begin() + pivot, array.end());

	EXPECT_TRUE(is_sorted(array.cbegin(), array.cbegin() + pivot));
}
