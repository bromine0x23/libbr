#include "../test.hpp"
#include <libbr/algorithm/all_of.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, all_of) {
	auto is_even = [](int x){ return x % 2 == 0; };
	auto is_less_then_ten = [](int x){ return x < 10; };
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		EXPECT_FALSE(all_of(array.cbegin(), array.cend(), is_even));

		EXPECT_TRUE(all_of(array.cbegin(), array.cend(), is_less_then_ten));
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		EXPECT_FALSE(all_of(list.cbegin(), list.cend(), is_even));

		EXPECT_TRUE(all_of(list.cbegin(), list.cend(), is_less_then_ten));
	} {
		SList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		EXPECT_FALSE(all_of(list.cbegin(), list.cend(), is_even));

		EXPECT_TRUE(all_of(list.cbegin(), list.cend(), is_less_then_ten));
	}
}
