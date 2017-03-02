#include "../test.hpp"
#include <libbr/algorithm/all_of.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, all_of) {
	{
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		EXPECT_FALSE(all_of(array.cbegin(), array.cend(), [](auto x){ return x % 2 == 0; }));

		EXPECT_TRUE(all_of(array.cbegin(), array.cend(), [](auto x){ return x < 10; }));
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		EXPECT_FALSE(all_of(list.cbegin(), list.cend(), [](auto x){ return x % 2 == 0; }));

		EXPECT_TRUE(all_of(list.cbegin(), list.cend(), [](auto x){ return x < 10; }));
	} {
		SList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		EXPECT_FALSE(all_of(list.cbegin(), list.cend(), [](auto x){ return x % 2 == 0; }));

		EXPECT_TRUE(all_of(list.cbegin(), list.cend(), [](auto x){ return x < 10; }));
	}
}
