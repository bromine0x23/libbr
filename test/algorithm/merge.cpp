#include "../test.hpp"
#include <libbr/algorithm/merge.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/insert_front_iterator.hpp>
#include <libbr/iterator/insert_iterator.hpp>

using namespace BR;

TEST(Algorithm, merge) {
	{
		DynamicArray<int> array0{ 0, 2, 4, 6, 7 };
		DynamicArray<int> array1{ 1, 3, 5, 8, 9 };
		DynamicArray<int> array;

		merge(array0.cbegin(), array0.cend(), array1.cbegin(), array1.cend(), make_insert_iterator(array, array.begin()));

		EXPECT_EQ((DynamicArray<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), array);
	} {
		DList<int> list0{ 0, 2, 4, 6, 8 };
		DList<int> list1{ 1, 3, 5, 7, 9 };
		DList<int> list;

		merge(list0.cbegin(), list0.cend(), list1.cbegin(), list1.cend(), make_insert_front_iterator(list));

		EXPECT_EQ((DList<int>{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 }), list);
	} {
		SList<int> list0{ 0, 2, 4, 6, 8 };
		SList<int> list1{ 1, 3, 5, 7, 9 };
		SList<int> list;

		merge(list0.cbegin(), list0.cend(), list1.cbegin(), list1.cend(), make_insert_front_iterator(list));

		EXPECT_EQ((SList<int>{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 }), list);
	}
}
