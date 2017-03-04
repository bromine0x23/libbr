#include "../test.hpp"
#include <libbr/algorithm/set_include.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/insert_front_iterator.hpp>
#include <libbr/iterator/insert_iterator.hpp>

using namespace BR;

TEST(Algorithm, set_include) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 7, 8 };

		DynamicArray<int> array0{ 1, 2, 7 };

		EXPECT_TRUE(set_include(array.cbegin(), array.cend(), array0.cbegin(), array0.cend()));

		DynamicArray<int> array1{ 5, 6, 7 };

		EXPECT_FALSE(set_include(array.cbegin(), array.cend(), array1.cbegin(), array1.cend()));
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 7, 8 };

		DList<int> list0{ 1, 2, 7 };

		EXPECT_TRUE(set_include(list.cbegin(), list.cend(), list0.cbegin(), list0.cend()));

		DList<int> list1{ 5, 6, 7 };

		EXPECT_FALSE(set_include(list.cbegin(), list.cend(), list1.cbegin(), list1.cend()));
	} {
		SList<int> list{ 1, 2, 3, 4, 5, 7, 8 };

		SList<int> list0{ 1, 2, 7 };

		EXPECT_TRUE(set_include(list.cbegin(), list.cend(), list0.cbegin(), list0.cend()));

		SList<int> list1{ 5, 6, 7 };

		EXPECT_FALSE(set_include(list.cbegin(), list.cend(), list1.cbegin(), list1.cend()));
	}
}
