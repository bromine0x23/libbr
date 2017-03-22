#include "../test.hpp"
#include <libbr/algorithm/any_of.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, any_of) {
	auto is_even = [](int x){ return x % 2 == 0; };
	auto is_congruence_to_eleven = [](int x){ return x % 11 == 0; };
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		EXPECT_TRUE(any_of(array.cbegin(), array.cend(), is_even));

		EXPECT_FALSE(any_of(array.cbegin(), array.cend(), is_congruence_to_eleven));
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		EXPECT_TRUE(any_of(list.cbegin(), list.cend(), is_even));

		EXPECT_FALSE(any_of(list.cbegin(), list.cend(), is_congruence_to_eleven));
	} {
		SList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		EXPECT_TRUE(any_of(list.cbegin(), list.cend(), is_even));

		EXPECT_FALSE(any_of(list.cbegin(), list.cend(), is_congruence_to_eleven));
	}
}
