#include "../test.hpp"
#include <libbr/algorithm/is_heap_until.hpp>

#include <libbr/algorithm/heap_build.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/iterator/distance.hpp>

using namespace BR;

TEST(Algorithm, is_heap_until) {
	DynamicArray<int> array{ 3, 1, 4, 1, 5, 9 };

	heap_build(array.begin(), array.end());

	EXPECT_EQ(6, distance(array.begin(), is_heap_until(array.begin(), array.end())));

	array.emplace_back(2);
	array.emplace_back(6);

	EXPECT_EQ(7, distance(array.begin(), is_heap_until(array.begin(), array.end())));
}
