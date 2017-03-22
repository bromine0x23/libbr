#include "../test.hpp"
#include <libbr/algorithm/copy_if.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/insert_back_iterator.hpp>
#include <libbr/iterator/insert_front_iterator.hpp>

using namespace BR;

TEST(Algorithm, copy_if) {
	auto is_even = [](int x){ return x % 2 == 0; };
	{
		DynamicArray<int> from_array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DynamicArray<int> to_array;

		copy_if(from_array.crbegin(), from_array.crend(), make_insert_back_iterator(to_array), is_even);

		EXPECT_EQ((DynamicArray<int>{ 8, 6, 4, 2 }), to_array);
	} {
		DList<int> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DList<int> to_list;

		copy_if(from_list.crbegin(), from_list.crend(), make_insert_back_iterator(to_list), is_even);

		EXPECT_EQ((DList<int>{ 8, 6, 4, 2 }), to_list);
	} {
		SList<int> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		SList<int> to_list;

		copy_if(from_list.cbegin(), from_list.cend(), make_insert_front_iterator(to_list), is_even);

		EXPECT_EQ((SList<int>{ 8, 6, 4, 2 }), to_list);
	}
}
