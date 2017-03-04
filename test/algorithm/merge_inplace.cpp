#include "../test.hpp"
#include <libbr/algorithm/merge_inplace.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/iterator/next.hpp>

using namespace BR;

TEST(Algorithm, merge_inplace) {
	{
		DynamicArray<int> array{ 0, 2, 4, 6, 7, 1, 3, 5, 8, 9 };

		merge_inplace(array.begin(), next(array.begin(), 5), array.end());

		EXPECT_EQ((DynamicArray<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), array);
	} {
		DList<int> list{ 0, 2, 4, 6, 7, 1, 3, 5, 8, 9 };

		merge_inplace(list.begin(), next(list.begin(), 5), list.end());

		EXPECT_EQ((DList<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), list);
	}
}
