#include "../test.hpp"
#include <libbr/algorithm/heap_build.hpp>

#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, heap_build) {
	DynamicArray<int> array{ 3, 1, 4, 1, 5, 9 };

	heap_build(array.begin(), array.end());

	EXPECT_EQ((DynamicArray<int>{ 9, 5, 4, 1, 1, 3 }), array);
}
