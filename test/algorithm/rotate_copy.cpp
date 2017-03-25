#include "../test.hpp"
#include <libbr/algorithm/rotate_copy.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/fixed_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/insert_back_iterator.hpp>
#include <libbr/iterator/insert_front_iterator.hpp>
#include <libbr/iterator/next.hpp>

using namespace BR;

TEST(Algorithm, rotate_copy) {
	{
		FixedArray<int, 9> from_array{{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }};

		FixedArray<int, 9> to_array;

		rotate_copy(from_array.cbegin(), next(from_array.cbegin(), 4), from_array.cend(), to_array.begin());

		EXPECT_EQ((FixedArray<int, 9>{{ 5, 6, 7, 8, 9, 1, 2, 3, 4 }}), to_array);
	} {
		DynamicArray<int> from_array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DynamicArray<int> to_array;

		rotate_copy(from_array.cbegin(), next(from_array.cbegin(), 4), from_array.cend(), make_insert_back_iterator(to_array));

		EXPECT_EQ((DynamicArray<int>{ 5, 6, 7, 8, 9, 1, 2, 3, 4 }), to_array);
	} {
		DList<int> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DList<int> to_list;

		rotate_copy(from_list.cbegin(), next(from_list.cbegin(), 4), from_list.cend(), make_insert_back_iterator(to_list));

		EXPECT_EQ((DList<int>{ 5, 6, 7, 8, 9, 1, 2, 3, 4 }), to_list);
	} {
		SList<int> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		SList<int> to_list;

		rotate_copy(from_list.cbegin(), next(from_list.cbegin(), 4), from_list.cend(), make_insert_front_iterator(to_list));
		EXPECT_EQ((SList<int>{ 4, 3, 2, 1, 9, 8, 7, 6, 5 }), to_list);
	}
}
