#include "../test.hpp"
#include <libbr/algorithm/copy.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/insert_back_iterator.hpp>
#include <libbr/iterator/insert_front_iterator.hpp>

using namespace BR;

TEST(Algorithm, copy) {
	{
		DynamicArray<int> from_array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DynamicArray<int> to_array;

		copy(from_array.crbegin(), from_array.crend(), make_insert_back_iterator(to_array));

		EXPECT_EQ((DynamicArray<int>{ 9, 8, 7, 6, 5, 4, 3, 2, 1 }), to_array);
	} {
		DList<int> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DList<int> to_list;

		copy(from_list.crbegin(), from_list.crend(), make_insert_back_iterator(to_list));

		EXPECT_EQ((DList<int>{ 9, 8, 7, 6, 5, 4, 3, 2, 1 }), to_list);
	} {
		SList<int> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		SList<int> to_list;

		copy(from_list.cbegin(), from_list.cend(), make_insert_front_iterator(to_list));

		EXPECT_EQ((SList<int>{ 9, 8, 7, 6, 5, 4, 3, 2, 1 }), to_list);
	}
}
