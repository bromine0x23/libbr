#include "../test.hpp"
#include <libbr/algorithm/remove_copy_if.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/insert_back_iterator.hpp>
#include <libbr/iterator/insert_front_iterator.hpp>

using namespace BR;

TEST(Algorithm, remove_copy_if) {
	auto is_even = [](auto x){ return x % 2 == 0; };
	{
		DynamicArray<int> from_array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DynamicArray<int> to_array;

		remove_copy_if(from_array.begin(), from_array.end(), make_insert_back_iterator(to_array), is_even);

		EXPECT_EQ((DynamicArray<int>{ 1, 3, 5, 7, 9 }), to_array);
	} {
		DList<int> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DList<int> to_list;

		remove_copy_if(from_list.begin(), from_list.end(), make_insert_back_iterator(to_list), is_even);

		EXPECT_EQ((DList<int>{ 1, 3, 5, 7, 9 }), to_list);
	} {
		SList<int> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		SList<int> to_list;

		remove_copy_if(from_list.begin(), from_list.end(), make_insert_front_iterator(to_list), is_even);

		EXPECT_EQ((SList<int>{ 9, 7, 5, 3, 1 }), to_list);
	}
}
