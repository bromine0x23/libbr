#include "../test.hpp"
#include <libbr/algorithm/set_intersection.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/insert_front_iterator.hpp>
#include <libbr/iterator/insert_iterator.hpp>

using namespace BR;

TEST(Algorithm, set_intersection) {
	{
		DynamicArray<int> array0{ 1, 2, 3, 4, 5, 6, 7, 8        };
		DynamicArray<int> array1{             5,    7,    9, 10 };
		DynamicArray<int> array;

		set_intersection(array0.cbegin(), array0.cend(), array1.cbegin(), array1.cend(), make_insert_iterator(array, array.begin()));

		EXPECT_EQ((DynamicArray<int>{ 5, 7 }), array);
	} {
		DList<int> list0{ 1, 2, 3, 4, 5, 6, 7, 8        };
		DList<int> list1{             5,    7,    9, 10 };
		DList<int> list;

		set_intersection(list0.cbegin(), list0.cend(), list1.cbegin(), list1.cend(), make_insert_front_iterator(list));

		EXPECT_EQ((DList<int>{ 7, 5 }), list);
	} {
		SList<int> list0{ 1, 2, 3, 4, 5, 6, 7, 8        };
		SList<int> list1{             5,    7,    9, 10 };
		SList<int> list;

		set_intersection(list0.cbegin(), list0.cend(), list1.cbegin(), list1.cend(), make_insert_front_iterator(list));

		EXPECT_EQ((SList<int>{ 7, 5 }), list);
	}
}
