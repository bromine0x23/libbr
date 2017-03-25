#include "../test.hpp"
#include <libbr/algorithm/reverse_copy.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/fixed_array.hpp>
#include <libbr/iterator/insert_back_iterator.hpp>

using namespace BR;

TEST(Algorithm, reverse_copy) {
	{
		FixedArray<int, 9> from_array{{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }};

		FixedArray<int, 9> to_array;

		reverse_copy(from_array.cbegin(), from_array.cend(), to_array.begin());

		EXPECT_EQ((FixedArray<int, 9>{{ 9, 8, 7, 6, 5, 4, 3, 2, 1 }}), to_array);
	} {
		DynamicArray<int> from_array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DynamicArray<int> to_array;

		reverse_copy(from_array.cbegin(), from_array.cend(), make_insert_back_iterator(to_array));

		EXPECT_EQ((DynamicArray<int>{ 9, 8, 7, 6, 5, 4, 3, 2, 1 }), to_array);
	} {
		DList<int> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DList<int> to_list;

		reverse_copy(from_list.cbegin(), from_list.cend(), make_insert_back_iterator(to_list));

		EXPECT_EQ((DList<int>{ 9, 8, 7, 6, 5, 4, 3, 2, 1 }), to_list);
	}
}
