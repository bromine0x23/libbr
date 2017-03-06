#include "../test.hpp"
#include <libbr/algorithm/replace_copy.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/insert_back_iterator.hpp>
#include <libbr/iterator/insert_front_iterator.hpp>

using namespace BR;

TEST(Algorithm, replace_copy) {
	{
		DynamicArray<int> from_array{ 1, 2, 3, 4, 2, 2, 3, 4 };

		DynamicArray<int> to_array;

		replace_copy(from_array.begin(), from_array.end(), make_insert_back_iterator(to_array), 2, 22);

		EXPECT_EQ((DynamicArray<int>{ 1, 22, 3, 4, 22, 22, 3, 4 }), to_array);
	} {
		DList<int> from_list{ 1, 2, 3, 4, 2, 2, 3, 4 };

		DList<int> to_list;

		replace_copy(from_list.begin(), from_list.end(), make_insert_back_iterator(to_list), 2, 22);

		EXPECT_EQ((DList<int>{ 1, 22, 3, 4, 22, 22, 3, 4 }), to_list);
	} {
		SList<int> from_list{ 1, 2, 3, 4, 2, 2, 3, 4 };

		SList<int> to_list;

		replace_copy(from_list.begin(), from_list.end(), make_insert_front_iterator(to_list), 2, 22);

		EXPECT_EQ((SList<int>{ 4, 3, 22, 22, 4, 3, 22, 1 }), to_list);
	}
}
