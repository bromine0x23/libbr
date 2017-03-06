#include "../test.hpp"
#include <libbr/algorithm/rotate.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/fixed_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/iterator/prev.hpp>

using namespace BR;

TEST(Algorithm, rotate) {
	{
		FixedArray<int, 9> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		rotate(array.begin(), next(array.begin(), 4), array.end());

		EXPECT_EQ((FixedArray<int, 9>{ 5, 6, 7, 8, 9, 1, 2, 3, 4 }), array);
	} {
		FixedArray<int, 9> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		rotate(array.begin(), next(array.begin(), 1), array.end());

		EXPECT_EQ((FixedArray<int, 9>{ 2, 3, 4, 5, 6, 7, 8, 9, 1 }), array);
	} {
		FixedArray<int, 9> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		rotate(array.begin(), prev(array.end(), 1), array.end());

		EXPECT_EQ((FixedArray<int, 9>{ 9, 1, 2, 3, 4, 5, 6, 7, 8 }), array);
	} {
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		rotate(array.begin(), next(array.begin(), 4), array.end());

		EXPECT_EQ((DynamicArray<int>{ 5, 6, 7, 8, 9, 1, 2, 3, 4 }), array);
	} {
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		rotate(array.begin(), next(array.begin(), 1), array.end());

		EXPECT_EQ((DynamicArray<int>{ 2, 3, 4, 5, 6, 7, 8, 9, 1 }), array);
	} {
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		rotate(array.begin(), prev(array.end(), 1), array.end());

		EXPECT_EQ((DynamicArray<int>{ 9, 1, 2, 3, 4, 5, 6, 7, 8 }), array);
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		rotate(list.begin(), next(list.begin(), 4), list.end());

		EXPECT_EQ((DList<int>{ 5, 6, 7, 8, 9, 1, 2, 3, 4 }), list);
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		rotate(list.begin(), next(list.begin(), 1), list.end());

		EXPECT_EQ((DList<int>{ 2, 3, 4, 5, 6, 7, 8, 9, 1 }), list);
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		rotate(list.begin(), prev(list.end(), 1), list.end());

		EXPECT_EQ((DList<int>{ 9, 1, 2, 3, 4, 5, 6, 7, 8 }), list);
	} {
		SList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		rotate(list.begin(), next(list.begin(), 4), list.end());

		EXPECT_EQ((SList<int>{ 5, 6, 7, 8, 9, 1, 2, 3, 4 }), list);
	} {
		SList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		rotate(list.begin(), next(list.begin(), 1), list.end());

		EXPECT_EQ((SList<int>{ 2, 3, 4, 5, 6, 7, 8, 9, 1 }), list);
	}
}
