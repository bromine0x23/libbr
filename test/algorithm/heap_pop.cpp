#include "../test.hpp"
#include <libbr/algorithm/heap_pop.hpp>

#include <libbr/algorithm/heap_build.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, heap_pop) {
	DynamicArray<int> array{ 3, 1, 4, 1, 5, 9 };

	heap_build(array.begin(), array.end());

	heap_pop(array.begin(), array.end());

	EXPECT_EQ((DynamicArray<int>{ 5, 3, 4, 1, 1, 9 }), array);
}
