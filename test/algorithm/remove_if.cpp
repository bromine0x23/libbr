#include "../test.hpp"
#include <libbr/algorithm/remove_if.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>

using namespace BR;

TEST(Algorithm, remove_if) {
	auto is_even = [](int x){ return x % 2 == 0; };
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		array.erase(remove_if(array.begin(), array.end(), is_even), array.end());

		EXPECT_EQ((DynamicArray<int>{ 1, 3, 5, 7, 9 }), array);
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		list.erase(remove_if(list.begin(), list.end(), is_even), list.end());

		EXPECT_EQ((DList<int>{ 1, 3, 5, 7, 9 }), list);
	}
}
