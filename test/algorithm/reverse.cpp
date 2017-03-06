#include "../test.hpp"
#include <libbr/algorithm/reverse.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/fixed_array.hpp>

using namespace BR;

TEST(Algorithm, reverse) {
	{
		FixedArray<int, 9> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		reverse(array.begin(), array.end());

		EXPECT_EQ((FixedArray<int, 9>{ 9, 8, 7, 6, 5, 4, 3, 2, 1 }), array);
	} {
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		reverse(array.begin(), array.end());

		EXPECT_EQ((DynamicArray<int>{ 9, 8, 7, 6, 5, 4, 3, 2, 1 }), array);
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		reverse(list.begin(), list.end());

		EXPECT_EQ((DList<int>{ 9, 8, 7, 6, 5, 4, 3, 2, 1 }), list);
	}
}
