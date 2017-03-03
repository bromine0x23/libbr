#include "../test.hpp"
#include <libbr/algorithm/is_sorted.hpp>

#include <libbr/algorithm/sort.hpp>
#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, is_sorted) {
	{
		DynamicArray<int> array{ 3, 1, 4, 1, 5, 9 };

		EXPECT_FALSE(is_sorted(array.cbegin(), array.cend()));
	} {
		DynamicArray<int> array{ 1, 2, 3, 4, 5 };

		EXPECT_TRUE(is_sorted(array.cbegin(), array.cend()));
	} {
		DList<int> list{ 3, 1, 4, 1, 5, 9 };

		EXPECT_FALSE(is_sorted(list.cbegin(), list.cend()));
	} {
		DList<int> list{ 1, 2, 3, 4, 5 };

		EXPECT_TRUE(is_sorted(list.cbegin(), list.cend()));
	} {
		SList<int> list{ 3, 1, 4, 1, 5, 9 };

		EXPECT_FALSE(is_sorted(list.cbegin(), list.cend()));
	} {
		SList<int> list{ 1, 2, 3, 4, 5 };

		EXPECT_TRUE(is_sorted(list.cbegin(), list.cend()));
	}
}
