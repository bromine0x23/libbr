#include "../test.hpp"
#include <libbr/algorithm/copy_if.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/iterator/insert_back_iterator.hpp>

using namespace BR;

TEST(Algorithm, copy_if) {
	{
		DynamicArray<int> from_array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DynamicArray<int> to_array;

		copy_if(from_array.crbegin(), from_array.crend(), make_insert_back_iterator(to_array), [](auto x){ return x % 2 == 0; });

		EXPECT_EQ((DynamicArray<int>{ 8, 6, 4, 2 }), to_array);
	} {
		DList<int> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DList<int> to_list;

		copy_if(from_list.crbegin(), from_list.crend(), make_insert_back_iterator(to_list), [](auto x){ return x % 2 == 0; });

		EXPECT_EQ((DList<int>{ 8, 6, 4, 2 }), to_list);
	}
}
