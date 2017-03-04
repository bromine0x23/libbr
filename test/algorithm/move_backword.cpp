#include "../test.hpp"
#include <libbr/algorithm/move_backward.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/iterator/insert_back_iterator.hpp>

using namespace BR;

TEST(Algorithm, move_backward) {
	{
		DynamicArray<int> from_array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DynamicArray<int> to_array(from_array.size());

		move_backward(from_array.cbegin(), from_array.cend(), to_array.end());

		EXPECT_EQ((DynamicArray<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }), to_array);
	} {
		DList<int> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		DList<int> to_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		move_backward(from_list.crbegin(), from_list.crend(), to_list.end());

		EXPECT_EQ((DList<int>{ 9, 8, 7, 6, 5, 4, 3, 2, 1 }), to_list);
	}
}
