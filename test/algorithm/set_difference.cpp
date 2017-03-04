#include "../test.hpp"
#include <libbr/algorithm/set_difference.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/insert_front_iterator.hpp>
#include <libbr/iterator/insert_iterator.hpp>

using namespace BR;

TEST(Algorithm, set_difference) {
	{
		DynamicArray<int> array0{ 1, 2, 5, 5, 5, 9 };
		DynamicArray<int> array1{ 2, 5, 7 };
		DynamicArray<int> array;

		set_difference(array0.cbegin(), array0.cend(), array1.cbegin(), array1.cend(), make_insert_iterator(array, array.begin()));

		EXPECT_EQ((DynamicArray<int>{ 1, 5, 5, 9 }), array);
	} {
		DList<int> list0{ 1, 2, 5, 5, 5, 9 };
		DList<int> list1{ 2, 5, 7 };
		DList<int> list;

		set_difference(list0.cbegin(), list0.cend(), list1.cbegin(), list1.cend(), make_insert_front_iterator(list));

		EXPECT_EQ((DList<int>{ 9, 5, 5, 1 }), list);
	} {
		SList<int> list0{ 1, 2, 5, 5, 5, 9 };
		SList<int> list1{ 2, 5, 7 };
		SList<int> list;

		set_difference(list0.cbegin(), list0.cend(), list1.cbegin(), list1.cend(), make_insert_front_iterator(list));

		EXPECT_EQ((SList<int>{ 9, 5, 5, 1 }), list);
	}
}
