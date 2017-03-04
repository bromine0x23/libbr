#include "../test.hpp"
#include <libbr/algorithm/set_union.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/insert_front_iterator.hpp>
#include <libbr/iterator/insert_iterator.hpp>

using namespace BR;

TEST(Algorithm, set_union) {
	{
		DynamicArray<int> array0{ 1, 2, 3, 4, 5, 6, 7, 8        };
		DynamicArray<int> array1{             5,    7,    9, 10 };
		DynamicArray<int> array;

		set_union(array0.cbegin(), array0.cend(), array1.cbegin(), array1.cend(), make_insert_iterator(array, array.begin()));

		EXPECT_EQ((DynamicArray<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }), array);
	} {
		DList<int> list0{ 1, 2, 3, 4, 5, 6, 7, 8        };
		DList<int> list1{             5,    7,    9, 10 };
		DList<int> list;

		set_union(list0.cbegin(), list0.cend(), list1.cbegin(), list1.cend(), make_insert_front_iterator(list));

		EXPECT_EQ((DList<int>{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }), list);
	} {
		SList<int> list0{ 1, 2, 3, 4, 5, 6, 7, 8        };
		SList<int> list1{             5,    7,    9, 10 };
		SList<int> list;

		set_union(list0.cbegin(), list0.cend(), list1.cbegin(), list1.cend(), make_insert_front_iterator(list));

		EXPECT_EQ((SList<int>{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }), list);
	}
}
