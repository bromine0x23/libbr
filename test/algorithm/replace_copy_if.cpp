#include "../test.hpp"
#include <libbr/algorithm/replace_copy_if.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/insert_back_iterator.hpp>
#include <libbr/iterator/insert_front_iterator.hpp>

using namespace BR;

TEST(Algorithm, replace_copy_if) {
	auto is_even = [](auto x){ return x % 2 == 0; };
	{
		DynamicArray<int> from_array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DynamicArray<int> to_array;

		replace_copy_if(from_array.begin(), from_array.end(), make_insert_back_iterator(to_array), is_even, 10);

		EXPECT_EQ((DynamicArray<int>{ 1, 10, 3, 10, 5, 10, 7, 10, 9 }), to_array);
	} {
		DList<int> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DList<int> to_list;

		replace_copy_if(from_list.begin(), from_list.end(), make_insert_back_iterator(to_list), is_even, 10);

		EXPECT_EQ((DList<int>{ 1, 10, 3, 10, 5, 10, 7, 10, 9 }), to_list);
	} {
		SList<int> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		SList<int> to_list;

		replace_copy_if(from_list.begin(), from_list.end(), make_insert_front_iterator(to_list), is_even, 10);

		EXPECT_EQ((SList<int>{ 9, 10, 7, 10, 5, 10, 3, 10, 1 }), to_list);
	}
}
