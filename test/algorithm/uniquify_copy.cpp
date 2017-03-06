#include "../test.hpp"
#include <libbr/algorithm/uniquify_copy.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/iterator/insert_back_iterator.hpp>

using namespace BR;

TEST(Algorithm, uniquify_copy) {
	{
		DynamicArray<int> from_array{ 1, 1, 2, 2, 3, 1, 1, 2, 3 };

		DynamicArray<int> to_array;

		uniquify_copy(from_array.cbegin(), from_array.cend(), make_insert_back_iterator(to_array));

		EXPECT_EQ((DynamicArray<int>{ 1, 2, 3, 1, 2, 3 }), to_array);
	} {
		DList<int> from_list{ 1, 1, 2, 2, 3, 1, 1, 2, 3 };

		DList<int> to_list;

		uniquify_copy(from_list.cbegin(), from_list.cend(), make_insert_back_iterator(to_list));

		EXPECT_EQ((DList<int>{ 1, 2, 3, 1, 2, 3 }), to_list);
	}
}