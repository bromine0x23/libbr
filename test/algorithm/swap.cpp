#include "../test.hpp"
#include <libbr/algorithm/swap.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, swap) {
	DynamicArray<int> array{ 1, 2, 3, 4, 5 };
	DList<int> list{ -1, -2, -3, -4, -5 };

	swap(array.begin(), array.end(), list.begin(), list.end());

	EXPECT_EQ((DynamicArray<int>{ -1, -2, -3, -4, -5 }), array);
	EXPECT_EQ((DList<int>{ 1, 2, 3, 4, 5 }), list);
}