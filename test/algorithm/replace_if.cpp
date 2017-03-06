#include "../test.hpp"
#include <libbr/algorithm/replace_if.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, replace_if) {
	auto is_even = [](auto x){ return x % 2 == 0; };
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		replace_if(array.begin(), array.end(), is_even, 10);

		EXPECT_EQ((DynamicArray<int>{ 1, 10, 3, 10, 5, 10, 7, 10, 9 }), array);
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		replace_if(list.begin(), list.end(), is_even, 10);

		EXPECT_EQ((DList<int>{ 1, 10, 3, 10, 5, 10, 7, 10, 9 }), list);
	} {
		SList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		replace_if(list.begin(), list.end(), is_even, 10);

		EXPECT_EQ((SList<int>{ 1, 10, 3, 10, 5, 10, 7, 10, 9 }), list);
	}
}
