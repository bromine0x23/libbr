#include "../test.hpp"
#include <libbr/algorithm/is_heap.hpp>

#include <libbr/algorithm/heap_build.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, is_heap) {
	DynamicArray<int> array{ 3, 1, 4, 1, 5, 9 };

	EXPECT_FALSE(is_heap(array.begin(), array.end()));

	heap_build(array.begin(), array.end());

	EXPECT_TRUE(is_heap(array.begin(), array.end()));
}
