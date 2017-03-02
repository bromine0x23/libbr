#include "../test.hpp"
#include <libbr/algorithm/heap_push.hpp>

#include <libbr/algorithm/heap_build.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, heap_push) {
	DynamicArray<int> array{ 3, 1, 4, 1, 5, 9 };

	heap_build(array.begin(), array.end());

	array.emplace_back(6);

	heap_push(array.begin(), array.end());

	EXPECT_EQ((DynamicArray<int>{ 9, 5, 6, 1, 1, 3, 4 }), array);
}
