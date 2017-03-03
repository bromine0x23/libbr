#include "../test.hpp"
#include <libbr/algorithm/is_permutation.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, is_permutation) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 5 };
		DynamicArray<int> array0{ 3, 5, 4, 1, 2 };
		DynamicArray<int> array1{ 3, 5, 4, 1, 1 };

		EXPECT_TRUE(is_permutation(array.cbegin(), array.cend(), array0.cbegin()));
		EXPECT_TRUE(is_permutation(array.cbegin(), array.cend(), array0.cbegin(), array0.cend()));
		EXPECT_FALSE(is_permutation(array.cbegin(), array.cend(), array1.cbegin()));
		EXPECT_FALSE(is_permutation(array.cbegin(), array.cend(), array1.cbegin(), array1.cend()));
	} {
		DList<int> list{ 1, 2, 3, 4, 5 };
		DList<int> list0{ 3, 5, 4, 1, 2 };
		DList<int> list1{ 3, 5, 4, 1, 1 };

		EXPECT_TRUE(is_permutation(list.cbegin(), list.cend(), list0.cbegin()));
		EXPECT_TRUE(is_permutation(list.cbegin(), list.cend(), list0.cbegin(), list0.cend()));
		EXPECT_FALSE(is_permutation(list.cbegin(), list.cend(), list1.cbegin()));
		EXPECT_FALSE(is_permutation(list.cbegin(), list.cend(), list1.cbegin(), list1.cend()));
	} {
		SList<int> list{ 1, 2, 3, 4, 5 };
		SList<int> list0{ 3, 5, 4, 1, 2 };
		SList<int> list1{ 3, 5, 4, 1, 1 };

		EXPECT_TRUE(is_permutation(list.cbegin(), list.cend(), list0.cbegin()));
		EXPECT_TRUE(is_permutation(list.cbegin(), list.cend(), list0.cbegin(), list0.cend()));
		EXPECT_FALSE(is_permutation(list.cbegin(), list.cend(), list1.cbegin()));
		EXPECT_FALSE(is_permutation(list.cbegin(), list.cend(), list1.cbegin(), list1.cend()));
	}
}
